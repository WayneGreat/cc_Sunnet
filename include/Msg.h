#pragma once
#include <memory>
using namespace std;

//消息基类
class BaseMsg {
public:
    enum TYPE
    {
        // 服务间消息类型
        SERVICE = 1,
        // 网络事件消息类型
        SCOKET_ACCEPT = 2, // 有新客户端连接时
        SCOKET_RW = 3, // 客户端可读可写
    };
    uint8_t type;           //消息类型
    char load[999999]{};    //用于检测内存泄漏，仅用于调试
    virtual ~BaseMsg(){};
};

// 继承
class ServiceMsg:public BaseMsg {
public:
    uint32_t source;            //消息发送方
    shared_ptr<char> buff;      //消息内容
    size_t size;                //消息内容大小
};

class ScoketAcceptMsg:public BaseMsg {
public:
    int listenFd; // 监听
    int clientFd; // 新连接的客户端
};

class ScoketRWMsg:public BaseMsg {
public:
    int fd; // 发生事件的套接字
    bool isRead = false;
    bool isWrite = false;
};