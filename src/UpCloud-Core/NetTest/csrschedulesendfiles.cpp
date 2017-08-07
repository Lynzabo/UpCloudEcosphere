#include "csrschedulesendfiles.h"

CsRScheduleSendFiles::CsRScheduleSendFiles()
{

}
QString CsRScheduleSendFiles::getUuid() const
{
    return uuid;
}

void CsRScheduleSendFiles::setUuid(const QString &value)
{
    uuid = value;
}
QString CsRScheduleSendFiles::getFileName() const
{
    return fileName;
}

void CsRScheduleSendFiles::setFileName(const QString &value)
{
    fileName = value;
}
QString CsRScheduleSendFiles::getDownUrl() const
{
    return downUrl;
}

void CsRScheduleSendFiles::setDownUrl(const QString &value)
{
    downUrl = value;
}
QString CsRScheduleSendFiles::getFileDestName() const
{
    return fileDestName;
}

void CsRScheduleSendFiles::setFileDestName(const QString &value)
{
    fileDestName = value;
}
QString CsRScheduleSendFiles::getSaveAbst() const
{
    return saveAbst;
}

void CsRScheduleSendFiles::setSaveAbst(const QString &value)
{
    saveAbst = value;
}
QString CsRScheduleSendFiles::getTaskUuid() const
{
    return taskUuid;
}

void CsRScheduleSendFiles::setTaskUuid(const QString &value)
{
    taskUuid = value;
}







