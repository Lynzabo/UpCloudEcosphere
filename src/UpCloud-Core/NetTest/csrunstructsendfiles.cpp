#include "csrunstructsendfiles.h"

CsRUnstructSendFiles::CsRUnstructSendFiles()
{

}
QString CsRUnstructSendFiles::getUuid() const
{
    return uuid;
}

void CsRUnstructSendFiles::setUuid(const QString &value)
{
    uuid = value;
}
QString CsRUnstructSendFiles::getFileName() const
{
    return fileName;
}

void CsRUnstructSendFiles::setFileName(const QString &value)
{
    fileName = value;
}
QString CsRUnstructSendFiles::getDownUrl() const
{
    return downUrl;
}

void CsRUnstructSendFiles::setDownUrl(const QString &value)
{
    downUrl = value;
}
QString CsRUnstructSendFiles::getFileDestName() const
{
    return fileDestName;
}

void CsRUnstructSendFiles::setFileDestName(const QString &value)
{
    fileDestName = value;
}
QString CsRUnstructSendFiles::getSaveAbst() const
{
    return saveAbst;
}

void CsRUnstructSendFiles::setSaveAbst(const QString &value)
{
    saveAbst = value;
}
quint32 CsRUnstructSendFiles::getTaskUuid() const
{
    return taskUuid;
}

void CsRUnstructSendFiles::setTaskUuid(const quint32 &value)
{
    taskUuid = value;
}







