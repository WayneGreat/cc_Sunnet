#include <iostream>
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

int main() {
    new Sunnet();
    Sunnet::inst->Start();//开启num个线程一直循环，指导触发退出
    //开启系统后处理逻辑
    Sunnet::inst->Wait(); //主线程在一直等待子线程退出
    return 0;
}
