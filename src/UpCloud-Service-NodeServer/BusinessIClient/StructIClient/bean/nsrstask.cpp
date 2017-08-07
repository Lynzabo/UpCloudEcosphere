#include "nsrstask.h"



QString NsRStructTask::getUuid() const
{
    return uuid;
}

void NsRStructTask::setUuid(const QString &value)
{
    uuid = value;
}

quint32 NsRStructTask::getTaskNum() const
{
    return taskNum;
}

void NsRStructTask::setTaskNum(const quint32 &value)
{
    taskNum = value;
}

quint16 NsRStructTask::getStrategy() const
{
    return strategy;
}

void NsRStructTask::setStrategy(const quint16 &value)
{
    strategy = value;
}

quint8 NsRStructTask::getState() const
{
    return state;
}

void NsRStructTask::setState(const quint8 &value)
{
    state = value;
}

QString NsRStructTask::getExecTime() const
{
    return execTime;
}

void NsRStructTask::setExecTime(const QString &value)
{
    execTime = value;
}

QString NsRStructTask::getInsertTime() const
{
    return insertTime;
}

void NsRStructTask::setInsertTime(const QString &value)
{
    insertTime = value;
}
NsRStructTask::NsRStructTask()
{

}

