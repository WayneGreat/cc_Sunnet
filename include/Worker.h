#pragma once
#include <thread>

//前向声明，解决循环引用问题
class Sunnet;
using namespace std;

class Worker
{
public:
    int id;             //编号
    int eachNum;        //每次处理多少条消息
    void operator()();  //线程函数 重载括号操作符
};



