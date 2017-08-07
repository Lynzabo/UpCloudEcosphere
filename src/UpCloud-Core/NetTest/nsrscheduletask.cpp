#include "nsrscheduletask.h"


QString NsRScheduleTask::getUuid() const
{
    return uuid;
}

void NsRScheduleTask::setUuid(const QString &value)
{
    uuid = value;
}

quint32 NsRScheduleTask::getTaskNum() const
{
    return taskNum;
}

void NsRScheduleTask::setTaskNum(const quint32 &value)
{
    taskNum = value;
}

quint16 NsRScheduleTask::getStrategy() const
{
    return strategy;
}

void NsRScheduleTask::setStrategy(const quint16 &value)
{
    strategy = value;
}

QChar NsRScheduleTask::getState() const
{
    return state;
}

void NsRScheduleTask::setState(const QChar &value)
{
    state = value;
}

QString NsRScheduleTask::getExecTime() const
{
    return execTime;
}

void NsRScheduleTask::setExecTime(const QString &value)
{
    execTime = value;
}

QString NsRScheduleTask::getSaveAbst() const
{
    return saveAbst;
}

void NsRScheduleTask::setSaveAbst(const QString &value)
{
    saveAbst = value;
}

QString NsRScheduleTask::getInsertTime() const
{
    return insertTime;
}

void NsRScheduleTask::setInsertTime(const QString &value)
{
    insertTime = value;
}
NsRScheduleTask::NsRScheduleTask()
{
    
}

