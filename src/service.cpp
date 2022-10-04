#include "Service.h"
#include "Sunnet.h"
#include <iostream>

Service::Service() {
    //初始化锁
    pthread_spin_init(&queueLock, PTHREAD_PROCESS_PRIVATE);
}

Service::~Service() {
    pthread_spin_destroy(&queueLock);
}

//插入消息
void Service::PushMsg(shared_ptr<BaseMsg> msg) {
    pthread_spin_lock(&queueLock);
    //pthread_spin_lock和pthread_spin_unlock的中间部分用花括号括起来，旨在提醒读者中间代码段处于锁中，称之为临界区
    {
        msgQueue.push(msg);//将消息入队
    }
    pthread_spin_unlock(&queueLock);
}

//取出消息
shared_ptr<BaseMsg> Service::PopMsg() {
    shared_ptr<BaseMsg> msg = NULL;
    //取出一条消息
    pthread_spin_lock(&queueLock);
    {
        //不为空队列
        if (!msgQueue.empty()) {
            msg = msgQueue.front();//获取队首元素
            msgQueue.pop();//将队首元素出队
        }
    }
    pthread_spin_unlock(&queueLock);
    return msg;
}

//创建服务后触发
void Service::Oninit() {
    cout << "[" << id << "] OnInit" << endl;
}

//收到消息时触发
void Service::OnMsg(shared_ptr<BaseMsg> msg) {
    cout << "[" << id << "] OnMsg" << endl;
}

//退出服务时触发
void Service::OnExit() {
    cout << "[" << id << "] OnExit" << endl;
}

//处理一条消息，返回值代表是否处理
bool Service::ProcessMsg() {
    shared_ptr<BaseMsg> msg = PopMsg();
    if (msg) {
        OnMsg(msg);
        return true;
    }
    else {
        return false; // 返回值代表队列是否为空
    }
}

//处理n条消息，返回值代表是否处理成功
void Service::ProcessMsgs(int max) {
    for (int i = 0; i < max; i++) {
        bool succ = ProcessMsg();
        if (!succ) {
            break;
        }
    }
}
