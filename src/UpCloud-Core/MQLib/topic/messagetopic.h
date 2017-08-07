#ifndef MESSAGETOPIC_H
#define MESSAGETOPIC_H
#include <QtCore>
#include "base.h"
#include "core/producer.h"
#include "core/consumer.h"
/**
 * @brief The MessageTopic class    消息控制主题
 * 不同优先级的消息将进入不同的生产者/消费者队列中
 */
class MessageTopic
{
public:
    //定义主题优先级,假如对于消费者来说,三种消费者队列中都有数据,优先让高优先级的进行出队,创建任务发送给中心处理
        //生产者的优先级则有消费者优先级决定,生产者和消费者唯一标示为UUID
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
public:
    MessageTopic();
    ~MessageTopic();
public:
    Producer *genProducer();
    Consumer *doPushWork(Producer *producer,MessageTopic::Priority priority = MessageTopic::NormalPriority);
    Producer *doPdWork(Consumer *consumer,MessageTopic::Priority priority = MessageTopic::NormalPriority);
    Producer *doPullWork();
    template<typename T>
    void close(T *obj);
private:
    /**
     * @brief enPdQueue    入生产者队列
     * @param producer
     * @param priority
     */
    void enPdQueue(Producer *producer = 0,MessageTopic::Priority priority = MessageTopic::NormalPriority);
    /**
     * @brief dePdQueue 出生产者队列
     * @param priority
     * @return
     */
    Producer *dePdQueue(const MessageTopic::Priority priority);
    /**
     * @brief enPdQueue    入消费者队列
     * @param consumer
     * @param priority
     */
    void enCsQueue(Consumer *consumer = 0,MessageTopic::Priority priority = MessageTopic::NormalPriority);
    /**
     * @brief dePdQueue 出消费者队列
     * @param priority
     * @return
     */
    Consumer *deCsQueue(const MessageTopic::Priority priority);
private:
    void clearQueues();
private:
    //生产者队列
    QQueue<Producer*> highProducers;
    QQueue<Producer*> normalProducers;
    QQueue<Producer*> lowProducers;//dsdsadasdasdas-Producer
    //消费者队列
    QQueue<Consumer*> highConsumers;
    QQueue<Consumer*> normalConsumers;
    QQueue<Consumer*> lowConsumers;//dsdsadasdasdas-Consumer
    QMutex *pdMutex;

};

#endif // MESSAGETOPIC_H
