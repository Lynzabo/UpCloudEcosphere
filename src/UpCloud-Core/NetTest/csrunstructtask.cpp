#include "csrunstructtask.h"


quint32 CsRUnstructTask::getTaskNum() const
{
    return taskNum;
}

void CsRUnstructTask::setTaskNum(const quint32 &value)
{
    taskNum = value;
}
CsRUnstructTask::CsRUnstructTask()
{
    
}
QString CsRUnstructTask::getUuid() const
{
    return uuid;
}

void CsRUnstructTask::setUuid(const QString &value)
{
    uuid = value;
}
QString CsRUnstructTask::getTaskName() const
{
    return taskName;
}

void CsRUnstructTask::setTaskName(const QString &value)
{
    taskName = value;
}

QString CsRUnstructTask::getDescription() const
{
    return description;
}

void CsRUnstructTask::setDescription(const QString &value)
{
    description = value;
}
QString CsRUnstructTask::getSendTime() const
{
    return sendTime;
}

void CsRUnstructTask::setSendTime(const QString &value)
{
    sendTime = value;
}
quint16 CsRUnstructTask::getStrategy() const
{
    return strategy;
}

void CsRUnstructTask::setStrategy(const quint16 &value)
{
    strategy = value;
}
QChar CsRUnstructTask::getState() const
{
    return state;
}

void CsRUnstructTask::setState(const QChar &value)
{
    state = value;
}
QString CsRUnstructTask::getInsertor() const
{
    return insertor;
}

void CsRUnstructTask::setInsertor(const QString &value)
{
    insertor = value;
}
QString CsRUnstructTask::getInsertTime() const
{
    return insertTime;
}

void CsRUnstructTask::setInsertTime(const QString &value)
{
    insertTime = value;
}
QString CsRUnstructTask::getOperater() const
{
    return operater;
}

void CsRUnstructTask::setOperater(const QString &value)
{
    operater = value;
}
QString CsRUnstructTask::getOperaTime() const
{
    return operaTime;
}

void CsRUnstructTask::setOperaTime(const QString &value)
{
    operaTime = value;
}












