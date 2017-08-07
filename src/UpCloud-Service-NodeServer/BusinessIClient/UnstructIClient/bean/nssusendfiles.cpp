#include "nssusendfiles.h"


QString NsSUnstructSendFiles::getUuid() const
{
    return uuid;
}

void NsSUnstructSendFiles::setUuid(const QString &value)
{
    uuid = value;
}

QString NsSUnstructSendFiles::getFileUrl() const
{
    return fileUrl;
}

void NsSUnstructSendFiles::setFileUrl(const QString &value)
{
    fileUrl = value;
}

QString NsSUnstructSendFiles::getFileAbst() const
{
    return fileAbst;
}

void NsSUnstructSendFiles::setFileAbst(const QString &value)
{
    fileAbst = value;
}

QString NsSUnstructSendFiles::getTaskUuid() const
{
    return taskUuid;
}

void NsSUnstructSendFiles::setTaskUuid(const QString &value)
{
    taskUuid = value;
}

quint8 NsSUnstructSendFiles::getState() const
{
    return state;
}

void NsSUnstructSendFiles::setState(const quint8 &value)
{
    state = value;
}

QString NsSUnstructSendFiles::getError() const
{
    return error;
}

void NsSUnstructSendFiles::setError(const QString &value)
{
    error = value;
}
NsSUnstructSendFiles::NsSUnstructSendFiles()
{
    
}

