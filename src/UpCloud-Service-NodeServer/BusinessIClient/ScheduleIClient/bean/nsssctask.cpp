#include "nsssctask.h"


QString NsSScheduleTask::getUuid() const
{
    return uuid;
}

void NsSScheduleTask::setUuid(const QString &value)
{
    uuid = value;
}

quint32 NsSScheduleTask::getTaskNum() const
{
    return taskNum;
}

void NsSScheduleTask::setTaskNum(const quint32 &value)
{
    taskNum = value;
}

quint16 NsSScheduleTask::getStrategy() const
{
    return strategy;
}

void NsSScheduleTask::setStrategy(const quint16 &value)
{
    strategy = value;
}

quint8 NsSScheduleTask::getState() const
{
    return state;
}

void NsSScheduleTask::setState(const quint8 &value)
{
    state = value;
}

QString NsSScheduleTask::getExecTime() const
{
    return execTime;
}

void NsSScheduleTask::setExecTime(const QString &value)
{
    execTime = value;
}

QString NsSScheduleTask::getSaveAbst() const
{
    return saveAbst;
}

void NsSScheduleTask::setSaveAbst(const QString &value)
{
    saveAbst = value;
}

QString NsSScheduleTask::getInsertTime() const
{
    return insertTime;
}

void NsSScheduleTask::setInsertTime(const QString &value)
{
    insertTime = value;
}
NsSScheduleTask::NsSScheduleTask()
{
    
}

