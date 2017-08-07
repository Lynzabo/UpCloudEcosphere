#include "nssutask.h"


QString NsSUnstructTask::getUuid() const
{
    return uuid;
}

void NsSUnstructTask::setUuid(const QString &value)
{
    uuid = value;
}

quint32 NsSUnstructTask::getTaskNum() const
{
    return taskNum;
}

void NsSUnstructTask::setTaskNum(const quint32 &value)
{
    taskNum = value;
}

quint16 NsSUnstructTask::getStrategy() const
{
    return strategy;
}

void NsSUnstructTask::setStrategy(const quint16 &value)
{
    strategy = value;
}

quint8 NsSUnstructTask::getState() const
{
    return state;
}

void NsSUnstructTask::setState(const quint8 &value)
{
    state = value;
}

QString NsSUnstructTask::getInsertTime() const
{
    return insertTime;
}

void NsSUnstructTask::setInsertTime(const QString &value)
{
    insertTime = value;
}
NsSUnstructTask::NsSUnstructTask()
{
    
}

