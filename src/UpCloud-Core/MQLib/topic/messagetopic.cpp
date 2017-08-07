#include "messagetopic.h"
MessageTopic::MessageTopic()
{
    clearQueues();
    pdMutex = new QMutex;
}
MessageTopic::~MessageTopic()
{
    clearQueues();
}

Producer* MessageTopic::genProducer()
{
    Producer *producer = new Producer;
    return producer;
}

Consumer *MessageTopic::doPushWork(Producer *producer, MessageTopic::Priority priority)
{
    QMutexLocker pdLocker(pdMutex);
    //未使用变量,防止编译时警告,使用Q_UNUSED扩住
    Q_UNUSED(pdLocker)
    enPdQueue(producer,priority);
    return deCsQueue(priority);
}

Producer *MessageTopic::doPdWork(Consumer *consumer, MessageTopic::Priority priority)
{
    enCsQueue(consumer,priority);
    return dePdQueue(priority);
}

Producer *MessageTopic::doPullWork()
{
    QMutexLocker pdLocker(pdMutex);
    //未使用变量,防止编译时警告,使用Q_UNUSED扩住
    Q_UNUSED(pdLocker)
    Producer *_pro = 0;
    if(highProducers.size()>0)
        _pro = dePdQueue(MessageTopic::HighPriority);
    if(normalProducers.size()>0)
        _pro = dePdQueue(MessageTopic::NormalPriority);
    if(lowProducers.size()>0)
        _pro = dePdQueue(MessageTopic::LowPriority);
    return _pro;
}

Producer *MessageTopic::dePdQueue(const MessageTopic::Priority priority)
{
    Producer *_pro = 0;
    switch (priority) {
    case MessageTopic::HighPriority:
        _pro = highProducers.dequeue();
        break;
    case MessageTopic::NormalPriority:
        _pro = normalProducers.dequeue();
        break;
    case MessageTopic::LowPriority:
        _pro = lowProducers.dequeue();
        break;
    default:
        break;
    }
    return _pro;
}

Consumer *MessageTopic::deCsQueue(const MessageTopic::Priority priority)
{
    return NULL;
}


template<typename T>
void MessageTopic::close(T *obj)
{
    delete obj;
    obj = NULL;
}

void MessageTopic::enPdQueue(Producer *producer, MessageTopic::Priority priority)
{
    switch (priority) {
    case MessageTopic::HighPriority:
        highProducers.enqueue(producer);
        break;
    case MessageTopic::NormalPriority:
        normalProducers.enqueue(producer);
        break;
    case MessageTopic::LowPriority:
        lowProducers.enqueue(producer);
        break;
    default:
        break;
    }
}

void MessageTopic::enCsQueue(Consumer *consumer, MessageTopic::Priority priority)
{
    switch (priority) {
    case MessageTopic::HighPriority:
        highConsumers.enqueue(consumer);
        break;
    case MessageTopic::NormalPriority:
        normalConsumers.enqueue(consumer);
        break;
    case MessageTopic::LowPriority:
        lowConsumers.enqueue(consumer);
        break;
    default:
        break;
    }
}


void MessageTopic::clearQueues()
{
    qDeleteAll(lowProducers);
    lowProducers.clear();
    qDeleteAll(normalProducers);
    normalProducers.clear();
    qDeleteAll(highProducers);
    highProducers.clear();
    qDeleteAll(lowConsumers);
    lowConsumers.clear();
    qDeleteAll(normalConsumers);
    normalConsumers.clear();
    qDeleteAll(highConsumers);
    highConsumers.clear();
}
