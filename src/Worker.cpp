#include <iostream>
#include <unistd.h>
#include "Worker.h"
#include "Service.h"
using namespace std;

void Worker::operator()() {
    while (true)
    {
        // cout << "working id:" << id << endl;
        // usleep(100000); //0.1s
        while (true) {
            shared_ptr<Service> srv = Sunnet::inst->PopGlobalQueue();
            if (!srv) {
                // usleep(100); //100微秒
                Sunnet::inst->WorkerWait(); //工作线程进入休眠，等待被唤醒
            }
            else {
                srv->ProcessMsgs(eachNum);
                CheckAndPutGlobal(srv);
            }
        }
    }
}

void Worker::CheckAndPutGlobal(shared_ptr<Service> srv) {
    //退出中
    if (srv->isExiting) {
        return;
    }

    pthread_spin_lock(&srv->queueLock);
    {
        //服务中的消息队列不为空，重新放回全局队列中
        if (!srv->msgQueue.empty()) {
            //此时inGlobal一定是true
            Sunnet::inst->PushGlobalQueue(srv);
        }
        else {
            //重设inGlobal
            srv->SetInGlobal(false);
        }
    }
    pthread_spin_unlock(&srv->queueLock);
}