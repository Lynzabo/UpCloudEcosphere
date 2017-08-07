#include "nssstructtask.h"


QString NsSStructTask::getUuid() const
{
    return uuid;
}

void NsSStructTask::setUuid(const QString &value)
{
    uuid = value;
}

quint32 NsSStructTask::getTaskNum() const
{
    return taskNum;
}

void NsSStructTask::setTaskNum(const quint32 &value)
{
    taskNum = value;
}

quint16 NsSStructTask::getStrategy() const
{
    return strategy;
}

void NsSStructTask::setStrategy(const quint16 &value)
{
    strategy = value;
}

QChar NsSStructTask::getState() const
{
    return state;
}

void NsSStructTask::setState(const QChar &value)
{
    state = value;
}

QString NsSStructTask::getExecTime() const
{
    return execTime;
}

void NsSStructTask::setExecTime(const QString &value)
{
    execTime = value;
}

QString NsSStructTask::getInsertTime() const
{
    return insertTime;
}

void NsSStructTask::setInsertTime(const QString &value)
{
    insertTime = value;
}
NsSStructTask::NsSStructTask()
{
    
}

