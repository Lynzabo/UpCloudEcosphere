#include "csrstructtask.h"

CsRStructTask::CsRStructTask()
{

}
QString CsRStructTask::getUuid() const
{
    return uuid;
}

void CsRStructTask::setUuid(const QString &value)
{
    uuid = value;
}
QString CsRStructTask::getTaskName() const
{
    return taskName;
}

void CsRStructTask::setTaskName(const QString &value)
{
    taskName = value;
}
quint32 CsRStructTask::getTaskNum() const
{
    return taskNum;
}

void CsRStructTask::setTaskNum(const quint32 &value)
{
    taskNum = value;
}
QString CsRStructTask::getDescription() const
{
    return description;
}

void CsRStructTask::setDescription(const QString &value)
{
    description = value;
}
QString CsRStructTask::getSendTime() const
{
    return sendTime;
}

void CsRStructTask::setSendTime(const QString &value)
{
    sendTime = value;
}
QString CsRStructTask::getExecTime() const
{
    return execTime;
}

void CsRStructTask::setExecTime(const QString &value)
{
    execTime = value;
}
quint16 CsRStructTask::getStrategy() const
{
    return strategy;
}

void CsRStructTask::setStrategy(const quint16 &value)
{
    strategy = value;
}
QChar CsRStructTask::getState() const
{
    return state;
}

void CsRStructTask::setState(const QChar &value)
{
    state = value;
}
QString CsRStructTask::getInsertor() const
{
    return insertor;
}

void CsRStructTask::setInsertor(const QString &value)
{
    insertor = value;
}
QString CsRStructTask::getInsertTime() const
{
    return insertTime;
}

void CsRStructTask::setInsertTime(const QString &value)
{
    insertTime = value;
}
QString CsRStructTask::getOperater() const
{
    return operater;
}

void CsRStructTask::setOperater(const QString &value)
{
    operater = value;
}
QString CsRStructTask::getOperaTime() const
{
    return operaTime;
}

void CsRStructTask::setOperaTime(const QString &value)
{
    operaTime = value;
}













