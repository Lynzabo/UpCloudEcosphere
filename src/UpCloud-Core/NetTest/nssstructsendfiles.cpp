#include "nssstructsendfiles.h"


QString NsSStructSendFiles::getUuid() const
{
    return uuid;
}

void NsSStructSendFiles::setUuid(const QString &value)
{
    uuid = value;
}

QString NsSStructSendFiles::getFileUrl() const
{
    return fileUrl;
}

void NsSStructSendFiles::setFileUrl(const QString &value)
{
    fileUrl = value;
}

QString NsSStructSendFiles::getFileAbst() const
{
    return fileAbst;
}

void NsSStructSendFiles::setFileAbst(const QString &value)
{
    fileAbst = value;
}

quint32 NsSStructSendFiles::getSequence() const
{
    return sequence;
}

void NsSStructSendFiles::setSequence(const quint32 &value)
{
    sequence = value;
}

QString NsSStructSendFiles::getTaskUuid() const
{
    return taskUuid;
}

void NsSStructSendFiles::setTaskUuid(const QString &value)
{
    taskUuid = value;
}

QChar NsSStructSendFiles::getState() const
{
    return state;
}

void NsSStructSendFiles::setState(const QChar &value)
{
    state = value;
}

QString NsSStructSendFiles::getError() const
{
    return error;
}

void NsSStructSendFiles::setError(const QString &value)
{
    error = value;
}
NsSStructSendFiles::NsSStructSendFiles()
{
    
}

