// 全局唯一，可代表整个系统
//一套Actor系统包含多个服务，Sunnet::inst管理着它们

class Sunnet
{
public:
    //单例
    static Sunnet* inst;
public:
    //构造函数
    Sunnet();
    //初始化并开始
    void Start();
};
