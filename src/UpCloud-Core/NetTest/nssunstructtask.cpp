#include "nssunstructtask.h"


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

QChar NsSUnstructTask::getState() const
{
    return state;
}

void NsSUnstructTask::setState(const QChar &value)
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

