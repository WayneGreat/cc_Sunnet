#include <iostream>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include "Sunnet.h"
using namespace std;

//单例
//拓展： 所谓单例，就是整个程序有且有一个实例，是一种常用的软件设计模式
//为了减少代码量，在代码中已假设用户只会创建一次Sunnet对象，并直接在构造函数中给静态变量赋值了
//所有头文件声明静态变量都需在源文件中定义
Sunnet* Sunnet::inst;

Sunnet::Sunnet() {
    inst = this;
}

//开启系统
void Sunnet::Start() {
    // cout << "Hello Sunnet" << endl;

    // 由于客户端断开连接后，服务器在还未完成四次挥手情况下还可以发送数据给客户端，这时客户端会回应复位（RST）信号
    // 导致服务器下次发送数据给客户端时，操作系统会向服务器发PIPE信号，造成进程终止，因此需要忽略

    // 忽略SIGPIPE信号
    signal(SIGPIPE, SIG_IGN); 

    //锁
    pthread_rwlock_init(&servicesLock, NULL);
    pthread_spin_init(&globalLock, PTHREAD_PROCESS_PRIVATE);
    pthread_mutex_init(&sleepMtx, NULL);
    assert(pthread_rwlock_init(&connsLock, NULL) == 0);
    //条件变量
    pthread_cond_init(&sleepCond, NULL);
    //开启Worker
    StartWorker();
    //开启Socket线程
    StartSocket();
}

void Sunnet::StartWorker() {
    for (int i = 0; i < WORKER_NUM; i++) {
        cout << "start worker thread:" << i << endl;
        //创建线程对象
        Worker* worker = new Worker();
        worker->id = i;
        worker->eachNum = 2 << i; //代表2的i次方
        //创建线程
        thread* wt = new thread(*worker);
        // 添加到数组中
        workers.push_back(worker);
        workerThreads.push_back(wt);
    }
}

void Sunnet::Wait() {
    if (workerThreads[0]) {
        workerThreads[0]->join();
    }
}

//新建服务
uint32_t Sunnet::NewService(shared_ptr<string> type) {
    auto srv = make_shared<Service>();
    srv->type = type;
    pthread_rwlock_wrlock(&servicesLock);
    {
        srv->id = maxId;
        maxId++;
        services.emplace(srv->id, srv); //构造及插入一个元素
    }
    pthread_rwlock_unlock(&servicesLock);
    srv->Oninit(); //初始化
    return srv->id;
}

//由id查找服务
shared_ptr<Service> Sunnet::GetService(uint32_t id) {
    shared_ptr<Service> srv = NULL;
    pthread_rwlock_rdlock(&servicesLock);
    {
        unordered_map<uint32_t, shared_ptr<Service>>::iterator iter = services.find(id);
        if (iter != services.end()) {
            srv = iter->second;
        }
    }
    pthread_rwlock_unlock(&servicesLock);
    return srv;
}

//删除服务
void Sunnet::KillService(uint32_t id) {
    shared_ptr<Service> srv = GetService(id);
    if (!srv) {
        return;
    }
    //退出前
    srv->OnExit();
    srv->isExiting = true; // 防止服务切断联系后有其他服务再发消息
    //删列表
    pthread_rwlock_wrlock(&servicesLock);
    {
        services.erase(id); //删除元素
    }
    pthread_rwlock_unlock(&servicesLock);
}

//弹出全局队列
shared_ptr<Service> Sunnet::PopGlobalQueue() {
    shared_ptr<Service> srv = NULL;
    pthread_spin_lock(&globalLock);
    {
        if (!globalQueue.empty()) {
            srv = globalQueue.front();
            globalQueue.pop();
            globalLen--;
        }
    }
    pthread_spin_unlock(&globalLock);
    return srv;
}

//插入全局队列
void Sunnet::PushGlobalQueue(shared_ptr<Service> srv) {
    pthread_spin_lock(&globalLock);
    {
        globalQueue.push(srv);
        globalLen++;
    }
    pthread_spin_unlock(&globalLock);
}

//发送消息
void Sunnet::Send(uint32_t toId, shared_ptr<BaseMsg> msg) {
    shared_ptr<Service> toSrv = GetService(toId);
    if (!toSrv) {
        cout << "Send fail, toSrv not exist toId:" << toId << endl;
        return;
    }
    //插入到目标服务的消息队列中
    toSrv->PushMsg(msg);
    //检查并加入到全局队列中等待工作线程处理
    bool hasPush = false;
    pthread_spin_lock(&toSrv->inGlobalLock);
    {
        if (!toSrv->inGlobal) {
            PushGlobalQueue(toSrv);
            toSrv->inGlobal = true;
            hasPush = true;
        }
    }
    pthread_spin_unlock(&toSrv->inGlobalLock);
    //唤醒线程，不在临界区内
    if (hasPush) {
        CheckAndWeakUp(); //由于send会被频繁调用，即不加锁会有出错可能性，但会提高运行效率
    }
}

//仅测试用，buff需new产生
shared_ptr<BaseMsg> Sunnet::MakeMsg(uint32_t source, char* buff, int len) {
    auto msg = make_shared<ServiceMsg>();
    msg->type = BaseMsg::TYPE::SERVICE;
    msg->source = source;
    //基本类型的对象没有析构函数，
    //所以用delete或delete[]都可以销毁基本类型数组
    //智能指针默认使用delete销毁对象，
    //所以无需重写智能指针的销毁方法
    msg->buff = shared_ptr<char>(buff);
    msg->size = len;
    return msg;
}

//Worker线程调用，进入休眠
void Sunnet::WorkerWait() {
    pthread_mutex_lock(&sleepMtx);
    {
        sleepCount++;
        pthread_cond_wait(&sleepCond, &sleepMtx);
        sleepCount--;
    }
    pthread_mutex_unlock(&sleepMtx);
}

// unsafe
void Sunnet::CheckAndWeakUp() {
    if (sleepCount == 0) {
        return;
    }

    //检测正在工作的线程是否足够
    if (WORKER_NUM - sleepCount <= globalLen) {
        cout << "weakup" << endl;
        pthread_cond_signal(&sleepCond);
    }
}

void Sunnet::StartSocket() {
    //创建线程对象
    socketWorker = new SocketWorker();
    //初始化
    socketWorker->Init();
    //创建线程
    socketThread = new thread(*socketWorker);
}

//  添加连接
int Sunnet::AddConn(int fd, uint32_t id, Conn::TYPE type) {
    auto conn = make_shared<Conn>();
    conn->fd = fd;
    conn->serviceId = id;
    conn->type = type;
    pthread_rwlock_wrlock(&connsLock);
    {
        conns.emplace(fd, conn);
    }
    pthread_rwlock_unlock(&connsLock);
    return fd;
}

// 通过id查找连接
shared_ptr<Conn> Sunnet::GetConn(int fd) {
    shared_ptr<Conn> conn = NULL;
    pthread_rwlock_rdlock(&connsLock);
    {
        unordered_map<uint32_t, shared_ptr<Conn>>::iterator iter = conns.find(fd);
        if (iter != conns.end()) {
            conn = iter->second;
        }
    }
    pthread_rwlock_unlock(&connsLock);
    return conn;
}

// 删除连接
bool Sunnet::RemoveConn(int fd) {
    int result;
    pthread_rwlock_wrlock(&connsLock);
    {
        result = conns.erase(fd);
    }
    pthread_rwlock_unlock(&connsLock);
    return result == 1;
}

int Sunnet::Listen(uint32_t port, uint32_t serviceId) {
    // 创建socket
    int listenFd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenFd <= 0) {
        cout << "listen error, listenFd <= 0 " << endl;
        return -1;
    }
    // 设置为非阻塞
    fcntl(listenFd, F_SETFL, O_NONBLOCK);

    // struct sockaddr_in {
    //     sa_family_t sin_family;  地址族
    //     in_port_t sin_port;      端口号，使用网络字节序
    //     struct in_addr sin_addr; ipv4地址结构体，使用网络字节序
    // }

    // struct in_addr {
    //     uint32_t s_addr;
    // }

    // #include<netinet/in.h>
    //  unsigned long int htol (unsigned long int hostlong);        主机字节序转换成网络字节序
    //  unsigned short int htons (unsigned short int hostshort);    主机字节序转换成网络字节序
    //  unsigned long int ntohl (unsigned long int netlong);        网络字节序转换成主机字节序
    //  unsigned short int ntohs (unsigned short int netshort);     网络字节序转换成主机字节序

    // bind
    struct sockaddr_in addr; // 创建地址结构，根据创建socket时的地址协议族确定
    addr.sin_family = AF_INET; // ipv4
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // 表示接收任意连接
    int r = bind(listenFd, (struct sockaddr*)&addr, sizeof(addr));
    if (r == -1) {
        cout << "listen error, bind fail" << endl;
        return -1;
    }
    // listen
    r = listen(listenFd, 64);
    if (r < 0) {
        return -1;
    }
    // 添加到管理结构
    AddConn(listenFd, serviceId, Conn::TYPE::LISTEN);
    // epoll事件，跨线程
    socketWorker->AddEvent(listenFd);
    return listenFd;
}

void Sunnet::CloseConn(uint32_t fd) {
    // 删除conn对象
    bool succ = RemoveConn(fd);
    // 关闭套接字
    close(fd);
    // 删除epoll对象套接字的监听（跨线程）
    if (succ) {
        socketWorker->RemoveEvent(fd);
    }
}
