#include <iostream>
#include <unistd.h>
#include "Sunnet.h"
// #include "cat.h"
using namespace std;

// int main()
// {
//     Cat cat1;
//     cat1.age = 5;
//     Cat cat2;
//     cat2.age = 2;
//     cat1.Say();
//     cat2.Say();
//     return 0;
// }

int test() {
    auto pingType = make_shared<string>("ping");
    uint32_t ping1 = Sunnet::inst->NewService(pingType);
    uint32_t ping2 = Sunnet::inst->NewService(pingType);
    uint32_t pong = Sunnet::inst->NewService(pingType);

    auto msg1 = Sunnet::inst->MakeMsg(
        ping1, new char[3] {'h', 'i', '\0'}, 3
    );

    auto msg2 = Sunnet::inst->MakeMsg(
        ping2, new char[6] {'h', 'e', 'l', 'l', 'o', '\0'}, 6
    );

    Sunnet::inst->Send(pong, msg1);
    Sunnet::inst->Send(pong, msg2);
}

int TestSocketCtrl() {
    int fd = Sunnet::inst->Listen(8001, 1);
    usleep(15 * 1000000); // 15s
    Sunnet::inst->CloseConn(fd);
}

int TestEcho() {
    auto t = make_shared<string>("gateway");
    uint32_t gateway = Sunnet::inst->NewService(t);
}

int main() {
    new Sunnet();
    Sunnet::inst->Start();//开启num个线程一直循环，直到触发退出
    // test();
    // TestSocketCtrl();
    // TestEcho();

    // 启动main服务
    auto t = make_shared<string>("main");
    Sunnet::inst->NewService(t); // 嵌入lua脚本

    //开启系统后处理逻辑
    Sunnet::inst->Wait(); //主线程在一直等待子线程退出
    return 0;
}
