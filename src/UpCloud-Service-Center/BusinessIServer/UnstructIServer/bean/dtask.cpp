#include "dtask.h"

DTask::DTask()
{

}
QString DTask::getTaskName() const
{
    return taskName;
}

void DTask::setTaskName(const QString &value)
{
    taskName = value;
}
QString DTask::getDescription() const
{
    return description;
}

void DTask::setDescription(const QString &value)
{
    description = value;
}
quint16 DTask::getStrategy() const
{
    return strategy;
}

void DTask::setStrategy(const quint16 &value)
{
    strategy = value;
}




