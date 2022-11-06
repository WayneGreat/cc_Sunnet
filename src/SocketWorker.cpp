#include "SocketWorker.h"
#include <iostream>
#include <unistd.h>
#include <assert.h>

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
        cout << "ScoketWorker working" << endl;
        usleep(1000);
    }
}
