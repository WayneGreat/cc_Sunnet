#pragma once
#include <vector>
#include "Worker.h"
#include "Service.h"
#include <unordered_map>

// 全局唯一，可代表整个系统
//一套Actor系统包含多个服务，Sunnet::inst管理着它们

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
};
