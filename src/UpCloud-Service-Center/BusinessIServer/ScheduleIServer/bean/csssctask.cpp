#include "csssctask.h"

CsSScheduleTask::CsSScheduleTask()
{

}
QString CsSScheduleTask::getUuid() const
{
    return uuid;
}

void CsSScheduleTask::setUuid(const QString &value)
{
    uuid = value;
}
QString CsSScheduleTask::getTaskName() const
{
    return taskName;
}

void CsSScheduleTask::setTaskName(const QString &value)
{
    taskName = value;
}
quint32 CsSScheduleTask::getTaskNum() const
{
    return taskNum;
}

void CsSScheduleTask::setTaskNum(const quint32 &value)
{
    taskNum = value;
}
QString CsSScheduleTask::getDescription() const
{
    return description;
}

void CsSScheduleTask::setDescription(const QString &value)
{
    description = value;
}
QString CsSScheduleTask::getSendTime() const
{
    return sendTime;
}

void CsSScheduleTask::setSendTime(const QString &value)
{
    sendTime = value;
}
QString CsSScheduleTask::getExecTime() const
{
    return execTime;
}

void CsSScheduleTask::setExecTime(const QString &value)
{
    execTime = value;
}
quint16 CsSScheduleTask::getStrategy() const
{
    return strategy;
}

void CsSScheduleTask::setStrategy(const quint16 &value)
{
    strategy = value;
}
quint8 CsSScheduleTask::getState() const
{
    return state;
}

void CsSScheduleTask::setState(const quint8 &value)
{
    state = value;
}
QString CsSScheduleTask::getSaveAbst() const
{
    return saveAbst;
}

void CsSScheduleTask::setSaveAbst(const QString &value)
{
    saveAbst = value;
}
QString CsSScheduleTask::getInsertor() const
{
    return insertor;
}

void CsSScheduleTask::setInsertor(const QString &value)
{
    insertor = value;
}
QString CsSScheduleTask::getInsertTime() const
{
    return insertTime;
}

void CsSScheduleTask::setInsertTime(const QString &value)
{
    insertTime = value;
}
QString CsSScheduleTask::getOperater() const
{
    return operater;
}

void CsSScheduleTask::setOperater(const QString &value)
{
    operater = value;
}
QString CsSScheduleTask::getOperaTime() const
{
    return operaTime;
}

void CsSScheduleTask::setOperaTime(const QString &value)
{
    operaTime = value;
}














