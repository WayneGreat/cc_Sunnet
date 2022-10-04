#include <iostream>
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
    //锁
    pthread_rwlock_init(&servicesLock, NULL);
    //开启Worker
    StartWorker();
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