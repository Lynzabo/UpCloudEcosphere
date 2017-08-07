#include "csrstructsendfiles.h"

CsRStructSendFiles::CsRStructSendFiles()
{

}
QString CsRStructSendFiles::getUuid() const
{
    return uuid;
}

void CsRStructSendFiles::setUuid(const QString &value)
{
    uuid = value;
}
QString CsRStructSendFiles::getFileName() const
{
    return fileName;
}

void CsRStructSendFiles::setFileName(const QString &value)
{
    fileName = value;
}
QString CsRStructSendFiles::getDownUrl() const
{
    return downUrl;
}

void CsRStructSendFiles::setDownUrl(const QString &value)
{
    downUrl = value;
}
QString CsRStructSendFiles::getFileDestName() const
{
    return fileDestName;
}

void CsRStructSendFiles::setFileDestName(const QString &value)
{
    fileDestName = value;
}
QString CsRStructSendFiles::getSaveAbst() const
{
    return saveAbst;
}

void CsRStructSendFiles::setSaveAbst(const QString &value)
{
    saveAbst = value;
}
quint32 CsRStructSendFiles::getSequence() const
{
    return sequence;
}

void CsRStructSendFiles::setSequence(const quint32 &value)
{
    sequence = value;
}
QString CsRStructSendFiles::getTaskUuid() const
{
    return taskUuid;
}

void CsRStructSendFiles::setTaskUuid(const QString &value)
{
    taskUuid = value;
}








