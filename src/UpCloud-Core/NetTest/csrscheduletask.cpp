#include "csrscheduletask.h"

CsRScheduleTask::CsRScheduleTask()
{

}
QString CsRScheduleTask::getUuid() const
{
    return uuid;
}

void CsRScheduleTask::setUuid(const QString &value)
{
    uuid = value;
}
QString CsRScheduleTask::getTaskName() const
{
    return taskName;
}

void CsRScheduleTask::setTaskName(const QString &value)
{
    taskName = value;
}
quint32 CsRScheduleTask::getTaskNum() const
{
    return taskNum;
}

void CsRScheduleTask::setTaskNum(const quint32 &value)
{
    taskNum = value;
}
QString CsRScheduleTask::getDescription() const
{
    return description;
}

void CsRScheduleTask::setDescription(const QString &value)
{
    description = value;
}
QString CsRScheduleTask::getSendTime() const
{
    return sendTime;
}

void CsRScheduleTask::setSendTime(const QString &value)
{
    sendTime = value;
}
QString CsRScheduleTask::getExecTime() const
{
    return execTime;
}

void CsRScheduleTask::setExecTime(const QString &value)
{
    execTime = value;
}
quint16 CsRScheduleTask::getStrategy() const
{
    return strategy;
}

void CsRScheduleTask::setStrategy(const quint16 &value)
{
    strategy = value;
}
QChar CsRScheduleTask::getState() const
{
    return state;
}

void CsRScheduleTask::setState(const QChar &value)
{
    state = value;
}
QString CsRScheduleTask::getSaveAbst() const
{
    return saveAbst;
}

void CsRScheduleTask::setSaveAbst(const QString &value)
{
    saveAbst = value;
}
QString CsRScheduleTask::getInsertor() const
{
    return insertor;
}

void CsRScheduleTask::setInsertor(const QString &value)
{
    insertor = value;
}
QString CsRScheduleTask::getInsertTime() const
{
    return insertTime;
}

void CsRScheduleTask::setInsertTime(const QString &value)
{
    insertTime = value;
}
QString CsRScheduleTask::getOperater() const
{
    return operater;
}

void CsRScheduleTask::setOperater(const QString &value)
{
    operater = value;
}
QString CsRScheduleTask::getOperaTime() const
{
    return operaTime;
}

void CsRScheduleTask::setOperaTime(const QString &value)
{
    operaTime = value;
}














