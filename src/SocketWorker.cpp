#include "SocketWorker.h"
#include "Sunnet.h"
#include <iostream>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>

//初始化
void SocketWorker::Init() {
    // cout << "ScoketWorker Init " << endl;
    cout << "SocketWorker Init" << endl;
    // 创建epoll对象
    epollFd = epoll_create(1024); // 返回值：非负数表示成功，-1表示失败
    assert(epollFd > 0);
}

void SocketWorker::operator()() {
    while(true) {
        // cout << "ScoketWorker working" << endl;
        // usleep(1000);
        // 阻塞等待
        const int EVENT_SIZE = 64;
        struct epoll_event events[EVENT_SIZE];
        int eventCount = epoll_wait(epollFd, events, EVENT_SIZE, -1);
        // 取得事件
        for (int i = 0; i < eventCount; i++) {
            // 处理事件
            epoll_event ev = events[i]; 
            OnEvent(ev);
        }
    }
}

// EPOLLIN 可读
// EPOLLOUT 可写
// EPOLLET 边缘触发，默认为水平触发

// 添加到epoll对象
void SocketWorker::AddEvent(int fd) {
    cout << "AddEvent fd " << fd << endl;
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET; // 使用边缘触发模式监听可读事件
    ev.data.fd = fd;
    if (epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &ev) == -1) {
        cout << "AddEvent epoll_ctl Fail:" << strerror(errno) << endl;
    }
}

// 从epoll对象中删除
void SocketWorker::RemoveEvent(int fd) {
    cout << "RemoveEvent fd " << fd << endl;
    epoll_ctl(epollFd, EPOLL_CTL_DEL, fd, NULL);
}

// 改变epoll对象中某个事件的模式
void SocketWorker::ModifyEvent(int fd, bool epollOut) {
    cout << "ModifyEvent fd " << fd << epollOut << endl;
    struct epoll_event ev;
    ev.data.fd = fd;

    if (epollOut) {
        ev.events = EPOLLIN | EPOLLET | EPOLLOUT;
    }
    else {
        ev.events = EPOLLIN | EPOLLET;
    }
    epoll_ctl(epollFd, EPOLL_CTL_MOD, fd, &ev);
}

//处理事件
void SocketWorker::OnEvent(epoll_event ev) {
    // cout << "OnEvent" << endl;
    int fd = ev.data.fd;
    cout << "OnEvent fd: " << fd << endl;
    auto conn = Sunnet::inst->GetConn(fd);
    if (conn == NULL) {
        cout << "OnEvent error, conn == NULL" << endl;
        return;
    }
    // 事件类型
    bool isRead = ev.events & EPOLLIN;
    bool isWrite = ev.events & EPOLLOUT;
    bool isError = ev.events & EPOLLERR;
    // 监听socket
    if (conn->type == Conn::TYPE::LISTEN) {
        if (isRead) {
            cout << "listen socket " << endl;
            OnAccept(conn);
        }
    }
    // 普通socket
    else {
            cout << "normal socket " << endl;
        if (isRead || isWrite) {
            OnRW(conn, isRead, isWrite);
        }
        if (isError) {
            cout << "OnError fd: " << conn->fd << endl;
        }
    }
}

void SocketWorker::OnAccept(shared_ptr<Conn> conn) {
    cout << "OnAccept fd: " << conn->fd << endl;
    // accept
    int clientFd = accept(conn->fd, NULL, NULL); // 返回代表客户端连接的套接字
    if (clientFd < 0) {
        cout << "accept error" << endl;
    }
    // 设置非阻塞
    fcntl(clientFd, F_SETFL, O_NONBLOCK);

    // 写缓冲区满问题 
    // 解决方法一: 设置写缓冲区大小
    unsigned long buffSize = 4294967295; // 4GB内存
    if (setsockopt(clientFd, SOL_SOCKET, SO_SNDBUFFORCE, &buffSize, sizeof(buffSize)) < 0) {
        cout << "OnAccept setsockopt Fail " << strerror(errno) << endl;
    }
    // 解决方法二: 自写缓冲区
    // 使用ConnWriter.h模块

    // 添加连接对象
    Sunnet::inst->AddConn(clientFd, conn->serviceId, Conn::TYPE::CLIENT);
    // 添加到epoll监听列表
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = clientFd;
    if (epoll_ctl(epollFd, EPOLL_CTL_ADD, clientFd, &ev) == -1) {
        cout << "OnAccept epoll_ctl Fail: " << strerror(errno) << endl;
    }
    // 通知服务
    auto msg = make_shared<SocketAcceptMsg>();
    msg->type = BaseMsg::TYPE::SCOKET_ACCEPT;
    msg->listenFd = conn->fd;
    msg->clientFd = clientFd;
    Sunnet::inst->Send(conn->serviceId, msg);
}

void SocketWorker::OnRW(shared_ptr<Conn> conn, bool r, bool w) {
    cout << "OnRW fd: " << conn->fd << endl;
    auto msg = make_shared<SocketRWMsg>();
    msg->type = BaseMsg::TYPE::SCOKET_RW;
    msg->fd = conn->fd;
    msg->isRead = r;
    msg->isWrite = w;
    Sunnet::inst->Send(conn->serviceId, msg);
}
