#pragma once
#include <thread>
#include "Sunnet.h"
#include "Service.h"

//前向声明，解决循环引用问题
class Sunnet;
using namespace std;

class Worker
{
public:
    int id;             //编号
    int eachNum;        //每次处理多少条消息
    void operator()();  //线程函数 重载括号操作符
private:
    void CheckAndPutGlobal(shared_ptr<Service> srv);
};



