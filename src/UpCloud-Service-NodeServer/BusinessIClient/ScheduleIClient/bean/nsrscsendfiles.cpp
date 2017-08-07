#include "nsrscsendfiles.h"


QString NsRScheduleSendFiles::getUuid() const
{
    return uuid;
}

void NsRScheduleSendFiles::setUuid(const QString &value)
{
    uuid = value;
}

QString NsRScheduleSendFiles::getFileUrl() const
{
    return fileUrl;
}

void NsRScheduleSendFiles::setFileUrl(const QString &value)
{
    fileUrl = value;
}

QString NsRScheduleSendFiles::getFileAbst() const
{
    return fileAbst;
}

void NsRScheduleSendFiles::setFileAbst(const QString &value)
{
    fileAbst = value;
}

QString NsRScheduleSendFiles::getTaskUuid() const
{
    return taskUuid;
}

void NsRScheduleSendFiles::setTaskUuid(const QString &value)
{
    taskUuid = value;
}

quint8 NsRScheduleSendFiles::getState() const
{
    return state;
}

void NsRScheduleSendFiles::setState(const quint8 &value)
{
    state = value;
}

QString NsRScheduleSendFiles::getError() const
{
    return error;
}

void NsRScheduleSendFiles::setError(const QString &value)
{
    error = value;
}
NsRScheduleSendFiles::NsRScheduleSendFiles()
{
    
}

