#ifndef DEPLEXDEFS_H
#define DEPLEXDEFS_H


class DeplexDefs
{
public:
    //定义发送者优先级,三种发送者队列中都有数据,优先让高优先级的进行出队,创建任务发送给中心处理
    enum Priority{
        //最高优先级,优先级最高,假若四种对列中都有数据,具有最高优先级的先出对,假若有低优先级的正在处理任务,如果最高优先级
             //有数据入队,立刻阻塞低优先级先让当前最高优先级先出队列
             //TODO 二期实现最高优先级功能
    //        HighestPriority,
        //高优先级,假若下面三种队列中都有数据,出队优先考虑高优先级
        HighPriority,
        //普通优先级,假若下面两种队列中都有数据,出队优先考虑普通优先级
        NormalPriority,
        //低优先级,当上面优先级队列中没有数据时候,低优先级的队列才出对
        LowPriority
    };
};

#endif // DEPLEXDEFS_H
