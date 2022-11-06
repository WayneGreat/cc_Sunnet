#pragma once
#include <vector>
#include "Worker.h"
#include "Service.h"
#include <unordered_map>
#include "SocketWorker.h"
#include "Conn.h"

// 全局唯一，可代表整个系统
//一套Actor系统包含多个服务，Sunnet::inst管理着它们

//Sunnet与Worker相互引用，需要在双方头文件中前置声明
class Worker;

class Sunnet
{
public:
    //单例
    static Sunnet* inst;
public:
    //构造函数
    Sunnet();
    //初始化并开始
    void Start();
    //等待运行
    void Wait();
public:
    //服务列表
    //哈希表的键是uint32_t类型，代表服务的id，值是shared_ptr<Service>类型，是服务对象的智能指针
    unordered_map<uint32_t, shared_ptr<Service>> services; //哈希表存储
    uint32_t maxId = 0; //最大ID
    pthread_rwlock_t servicesLock; //服务使用的读写锁
public:
    //增删服务
    uint32_t NewService(shared_ptr<string> type);
    void KillService(uint32_t id); //仅限服务自己调用
public:
    //发送消息
    void Send(uint32_t toId, shared_ptr<BaseMsg> msg);
    //全局队列操作
    shared_ptr<Service> PopGlobalQueue();
    void PushGlobalQueue(shared_ptr<Service> srv);
public:
    shared_ptr<BaseMsg> MakeMsg(uint32_t source, char* buff, int len);
public:
    //唤醒工作线程
    void CheckAndWeakUp();
    //让工作线程等待（仅工作线程调用）
    void WorkerWait();
public:
    //增删查Conn
    int AddConn(int fd, uint32_t id, Conn::TYPE type);
    shared_ptr<Conn> GetConn(int fd);
    bool RemoveConn(int fd);

private:
    //工作线程
    int WORKER_NUM = 3;             //工作线程数
    vector<Worker*> workers;        //worker对象
    vector<thread*> workerThreads;  //线程
private:
    //开启工作线程
    void StartWorker();
private:
    //获取服务
    shared_ptr<Service> GetService(uint32_t id);
private:
    queue<shared_ptr<Service>> globalQueue;
    int globalLen = 0;             //队列长度
    pthread_spinlock_t globalLock; //锁
private:
    //休眠和唤醒
    pthread_mutex_t sleepMtx; //互斥锁
    pthread_cond_t sleepCond; //条件变量
    int sleepCount = 0;       //休眠工作线程数
private:
    //socket线程
    SocketWorker* socketWorker;
    thread* socketThread;
private:
    //开启Socket线程
    void StartSocket();
private:
    //Conn列表
    //哈希表的键是uint32_t类型，代表服务的id，值是shared_ptr<Service>类型，是连接对象的智能指针
    unordered_map<uint32_t, shared_ptr<Conn>> conns;
    pthread_rwlock_t connsLock; // 读写锁
};
