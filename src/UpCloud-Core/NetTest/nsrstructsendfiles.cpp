#include "nsrstructsendfiles.h"


QString NsRStructSendFiles::getUuid() const
{
    return uuid;
}

void NsRStructSendFiles::setUuid(const QString &value)
{
    uuid = value;
}

QString NsRStructSendFiles::getFileUrl() const
{
    return fileUrl;
}

void NsRStructSendFiles::setFileUrl(const QString &value)
{
    fileUrl = value;
}

QString NsRStructSendFiles::getFileAbst() const
{
    return fileAbst;
}

void NsRStructSendFiles::setFileAbst(const QString &value)
{
    fileAbst = value;
}

quint32 NsRStructSendFiles::getSequence() const
{
    return sequence;
}

void NsRStructSendFiles::setSequence(const quint32 &value)
{
    sequence = value;
}

QString NsRStructSendFiles::getTaskUuid() const
{
    return taskUuid;
}

void NsRStructSendFiles::setTaskUuid(const QString &value)
{
    taskUuid = value;
}

QChar NsRStructSendFiles::getState() const
{
    return state;
}

void NsRStructSendFiles::setState(const QChar &value)
{
    state = value;
}

QString NsRStructSendFiles::getError() const
{
    return error;
}

void NsRStructSendFiles::setError(const QString &value)
{
    error = value;
}
NsRStructSendFiles::NsRStructSendFiles()
{
    
}

