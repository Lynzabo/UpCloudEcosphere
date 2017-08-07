#ifndef MQPOOL_H
#define MQPOOL_H
#include "mqlib_global.h"
#include "base.h"
#include "topic/messagetopic.h"
//异步非阻塞全双工通讯
//class FDuplex
//{
//public:
//    FDuplex(MessageTopic::Priority priority = MessageTopic::NormalPriority)
//    {

//    }
//public:
//    virtual void onPreExecute() = 0;//可以修改UI
//    virtual void doInBackground() = 0;
//    virtual void callback() = 0;
//    virtual void onPostExecute() = 0;
//};
class MQLIBSHARED_EXPORT MQPool:QObject
{
    Q_OBJECT
    SINGLETON(MQPool)
public:
    /**
     * @brief genProducer   生成生产者
     * @param priority
     * @return
     */
    Producer *genProducer();
    /**
     * @brief doPushWork    执行任务
     * @param producer
     * @return
     */
    Consumer *doPushWork(Producer *producer,MessageTopic::Priority priority = MessageTopic::NormalPriority);
    /**
     * @brief doPullWork   返回要执行的任务
     * @return
     */
    Producer *doPullWork();
    /**
     *释放消费者/生产者资源
     */
    template<typename T>
    void close(T *obj);

private:
    MessageTopic *msgTopic;
};

#endif // MQPOOL_H
