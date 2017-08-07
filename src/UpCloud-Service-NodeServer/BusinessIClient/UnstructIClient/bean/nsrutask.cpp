#include "nsrutask.h"
QString NsRUnstructTask::getUuid() const
{
    return uuid;
}

void NsRUnstructTask::setUuid(const QString &value)
{
    uuid = value;
}

quint32 NsRUnstructTask::getTaskNum() const
{
    return taskNum;
}

void NsRUnstructTask::setTaskNum(const quint32 &value)
{
    taskNum = value;
}

quint16 NsRUnstructTask::getStrategy() const
{
    return strategy;
}

void NsRUnstructTask::setStrategy(const quint16 &value)
{
    strategy = value;
}

quint8 NsRUnstructTask::getState() const
{
    return state;
}

void NsRUnstructTask::setState(const quint8 &value)
{
    state = value;
}

QString NsRUnstructTask::getInsertTime() const
{
    return insertTime;
}

void NsRUnstructTask::setInsertTime(const QString &value)
{
    insertTime = value;
}
NsRUnstructTask::NsRUnstructTask()
{

}

