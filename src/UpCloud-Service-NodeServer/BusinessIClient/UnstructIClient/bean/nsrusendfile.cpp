#include "nsrusendfiles.h"
QString NsRUnstructSendFiles::getUuid() const
{
    return uuid;
}

void NsRUnstructSendFiles::setUuid(const QString &value)
{
    uuid = value;
}

QString NsRUnstructSendFiles::getFileUrl() const
{
    return fileUrl;
}

void NsRUnstructSendFiles::setFileUrl(const QString &value)
{
    fileUrl = value;
}

QString NsRUnstructSendFiles::getFileAbst() const
{
    return fileAbst;
}

void NsRUnstructSendFiles::setFileAbst(const QString &value)
{
    fileAbst = value;
}

QString NsRUnstructSendFiles::getTaskUuid() const
{
    return taskUuid;
}

void NsRUnstructSendFiles::setTaskUuid(const QString &value)
{
    taskUuid = value;
}

quint8 NsRUnstructSendFiles::getState() const
{
    return state;
}

void NsRUnstructSendFiles::setState(const quint8 &value)
{
    state = value;
}

QString NsRUnstructSendFiles::getError() const
{
    return error;
}

void NsRUnstructSendFiles::setError(const QString &value)
{
    error = value;
}
NsRUnstructSendFiles::NsRUnstructSendFiles()
{

}

