#include <iostream>
#include "Sunnet.h"
using namespace std;

//单例
//拓展： 所谓单例，就是整个程序有且有一个实例，是一种常用的软件设计模式
//为了减少代码量，在代码中已假设用户只会创建一次Sunnet对象，并直接在构造函数中给静态变量赋值了
//所有头文件声明静态变量都需在源文件中定义
Sunnet* Sunnet::inst;

Sunnet::Sunnet() {
    inst = this;
}

//开启系统
void Sunnet::Start() {
    cout << "Hello Sunnet" << endl;
}