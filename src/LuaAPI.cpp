#include "LuaAPI.h"
#include "Sunnet.h"
#include <stdint.h>
#include <unistd.h>
#include <string.h>

// 当Lua调用C++时，被调用的方法会得到一个新的栈，新栈中包含了Lua传递给C++的所有参数，而C++方法需要把返回的结果放入栈中，以返回给调用者
// C++方法有一套固定的编写套路，一般分为 “获取参数、处理、返回结果” 三个步骤

int LuaAPI::NewService(lua_State *luaState) {
    // 参数个数
    int num = lua_gettop(luaState); // 获取参数个数

    // 参数1：服务类型
    if (lua_isstring(luaState, 1) == 0) { // 1:是字符串 0:不是字符串，当num为1时，等价于lua_isstring(..., -1)
        // 返回错误值-1
        lua_pushinteger(luaState, -1);
        return 1;
    }

    // 服务类的type属性会贯穿服务的整个生命周期，而且Lua字符串是由Lua虚拟机管理的
    // Lua虚拟机带有垃圾回收机制，当它判断Lua代码不再使用某些元素时，会释放掉它们以节省内存
    // 用memcpy将字符串复制了一份，以避免可能发生的冲突
    size_t len = 0;
    const char *type = lua_tolstring(luaState, 1, &len);
    char *newstr = new char[len+1]; // 多一个位置在字符串后面加\0
    newstr[len] = '\0';
    memcpy(newstr, type, len);
    auto t = make_shared<string>(newstr);
    // 处理
    uint32_t id = Sunnet::inst->NewService(t);
    // 返回值: 服务id
    lua_pushinteger(luaState, id);
    return 1; // 代表了Lua方法的返回值个数
}

// 注册模块，在初始化阶段调用
void LuaAPI::Register(lua_State *luaState) {
    static luaL_Reg lualibs[] = {
        {"NewService", NewService}, // 第一个代表Lua中的方法名字，第二个对于于C++方法
        // {"KillService", KillService},
        // {"Send", Send},
        // {"Listen", Listen},
        // {"CloseConn", CloseConn},
        // {"Write", Write},
        {NULL, NULL},
    };
    // 相当于是在Lua中新建了一个名为sunnet的全局表，表中包含了NewService这个C++方法
    luaL_newlib(luaState, lualibs);
    lua_setglobal(luaState, "sunnet");
}