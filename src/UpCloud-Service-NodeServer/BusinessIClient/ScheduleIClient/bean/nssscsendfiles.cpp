#include "nssscsendfiles.h"


QString NsSScheduleSendFiles::getUuid() const
{
    return uuid;
}

void NsSScheduleSendFiles::setUuid(const QString &value)
{
    uuid = value;
}

QString NsSScheduleSendFiles::getFileUrl() const
{
    return fileUrl;
}

void NsSScheduleSendFiles::setFileUrl(const QString &value)
{
    fileUrl = value;
}

QString NsSScheduleSendFiles::getFileAbst() const
{
    return fileAbst;
}

void NsSScheduleSendFiles::setFileAbst(const QString &value)
{
    fileAbst = value;
}

QString NsSScheduleSendFiles::getTaskUuid() const
{
    return taskUuid;
}

void NsSScheduleSendFiles::setTaskUuid(const QString &value)
{
    taskUuid = value;
}

QString NsSScheduleSendFiles::getState() const
{
    return state;
}

void NsSScheduleSendFiles::setState(const QString &value)
{
    state = value;
}

QString NsSScheduleSendFiles::getError() const
{
    return error;
}

void NsSScheduleSendFiles::setError(const QString &value)
{
    error = value;
}
NsSScheduleSendFiles::NsSScheduleSendFiles()
{
    
}

