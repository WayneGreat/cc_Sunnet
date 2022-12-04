#include "Service.h"
#include "Sunnet.h"
#include "LuaAPI.h"
#include <iostream>
#include <unistd.h>
#include <string.h>

Service::Service() {
    //初始化锁
    pthread_spin_init(&queueLock, PTHREAD_PROCESS_PRIVATE);
    pthread_spin_init(&inGlobalLock, PTHREAD_PROCESS_PRIVATE);
}

Service::~Service() {
    pthread_spin_destroy(&queueLock);
    pthread_spin_destroy(&inGlobalLock);
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
    // 开启监听
    // Sunnet::inst->Listen(8002, id);

    // 新建Lua虚拟机
    luaState = luaL_newstate();
    luaL_openlibs(luaState);

    // 注册Sunnet系统API：增强Lua脚本功能
    LuaAPI::Register(luaState);

    // 执行Lua文件
    string filename = "../service/" + *type + "/init.lua";
    int isok = luaL_dofile(luaState, filename.data());
    if (isok == 1) { // 若成功则返回0，失败为1
        cout << "run lua fail: " << lua_tostring(luaState, -1) << endl;
    }
    // 调用Lua函数
    lua_getglobal(luaState, "OnInit");
    lua_pushinteger(luaState, id);
    isok = lua_pcall(luaState, 1, 0, 0);
    if (isok != 0) { // 返回值为0代表成功，否则代表失败
        cout << "call lua OnInit fail " << lua_tostring(luaState, -1) << endl;
    }
}

//收到消息时触发
void Service::OnMsg(shared_ptr<BaseMsg> msg) {
    //测试用
    // if (msg->type == BaseMsg::TYPE::SERVICE) {
    //     auto m = dynamic_pointer_cast<ServiceMsg>(msg);
    //     cout << "[" << id << "] OnMsg " << m->buff <<endl;

    //     auto msgRet = Sunnet::inst->MakeMsg(
    //         id, new char[9999999]{'p', 'i', 'n', 'g', '\0'}, 9999999);

    //     Sunnet::inst->Send(m->source, msgRet);
    // }
    // else {
    //     cout << "[" << id << "] OnMsg" << endl;
    // }

    // 将read, write, close封装
    // SERVICE
    if (msg->type == BaseMsg::TYPE::SERVICE) {
        auto m = dynamic_pointer_cast<ServiceMsg>(msg);
        OnServiceMsg(m);
    }
    // SOCKET_ACCEPT
    else if (msg->type == BaseMsg::TYPE::SCOKET_ACCEPT) {
        auto m = dynamic_pointer_cast<SocketAcceptMsg>(msg);
        OnAcceptMsg(m);
    }
    // SOCKET_RW
    else if (msg->type == BaseMsg::TYPE::SCOKET_RW) {
        auto m = dynamic_pointer_cast<SocketRWMsg>(msg);
        // if (m->isRead) {
        //     char buff[512];
        //     int len = read(m->fd, &buff, 512);
        //     if (len > 0 ) {
        //         char writeBuff[3] = {'l', 'p', 'y'};
        //         write(m->fd, &writeBuff, 3);
        //     }
        //     else {
        //         cout << "close " << m->fd << " " << strerror(errno) << endl;
        //         Sunnet::inst->CloseConn(m->fd);
        //     }
        // }
        OnRWMsg(m);
    }
}

//退出服务时触发
void Service::OnExit() {
    cout << "[" << id << "] OnExit" << endl;
    // 调用Lua函数
    lua_getglobal(luaState, "OnExit");
    int isok = lua_pcall(luaState, 0, 0, 0);
    if (isok != 0) { // 非0为失败
        cout << "call lua OnExit fail " << lua_tostring(luaState, -1) << endl;
    }
    // 关闭Lua虚拟机
    lua_close(luaState);
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

void Service::SetInGlobal(bool isIn) {
    pthread_spin_lock(&inGlobalLock);
    {
        inGlobal = isIn;
    }
    pthread_spin_unlock(&inGlobalLock);
}

void Service::OnServiceMsg(shared_ptr<ServiceMsg> msg) {
    cout << "OnServiceMsg" << endl;
}

void Service::OnAcceptMsg(shared_ptr<SocketAcceptMsg> msg) {
    cout << "OnAcceptMsg" << msg->clientFd << endl;
}

void Service::OnRWMsg(shared_ptr<SocketRWMsg> msg) {
    int fd = msg->fd;
    //可读
    if (msg->isRead) {
        const int BUFFSIZE = 512;
        char buff[BUFFSIZE];
        int len = 0;

        do {
            len = read(fd, &buff, BUFFSIZE);
            if (len > 0) {
                OnSocketData(fd, buff, len);
            }
        } while(len == BUFFSIZE); 
        // 如果恰好有512字节数据被read，下一处循环中，read会返回-1，并设置errno为EAGAIN，即不会进入读取失败的分支

        if (len <= 0 && errno != EAGAIN) {
            if (Sunnet::inst->GetConn(fd)) { // 若服务器主动断开连接，在处理时需要判断conn对象是否还未被释放，不然处理两次OnSocketClose会出错
                OnSocketClose(fd);
                Sunnet::inst->CloseConn(fd);
            }
        }
    }
    //可写
    if (msg->isWrite) {
        if(Sunnet::inst->GetConn(fd)) {
            OnSocketWriteable(fd);
        }
    }
}

// 收到客户端消息
void Service::OnSocketData(int fd, const char* buff, int len) {
    cout << "OnSocketData" << fd << " buff: " << buff << endl;
    //echo
    char writeBuff[3] = {'l', 'p', 'y'};
    write(fd, &writeBuff, 3);
}

// 套接字可写
void Service::OnSocketWriteable(int fd) {
    cout << "OnSocketWriteable" << endl;
}

// 关闭连接前
void Service::OnSocketClose(int fd) {
    cout << "OnSocketClose" << fd << endl;
}
