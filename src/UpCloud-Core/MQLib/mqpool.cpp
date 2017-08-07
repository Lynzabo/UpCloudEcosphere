#include "mqpool.h"
MQPool::MQPool()
{
    msgTopic = new MessageTopic;
}
MQPool::~MQPool()
{
    delete msgTopic;
    msgTopic = NULL;
}
Producer* MQPool::genProducer()
{
    return msgTopic->genProducer();
}

Consumer *MQPool::doPushWork(Producer *producer, MessageTopic::Priority priority)
{
    return msgTopic->doPushWork(producer,priority);
}

Producer *MQPool::doPullWork()
{
    Producer *_pro = 0;
    while(_pro == NULL)
    {
        _pro = msgTopic->doPullWork();
        QThread::sleep(5);
    }
    return _pro;
}
template<typename T>
void MQPool::close(T *obj)
{
    return msgTopic->close(obj);
}

SINGLETON_INITIALIZE(MQPool)
