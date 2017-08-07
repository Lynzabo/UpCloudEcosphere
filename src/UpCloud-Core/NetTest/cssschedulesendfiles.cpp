#include "cssschedulesendfiles.h"

CsSScheduleSendFiles::CsSScheduleSendFiles()
{

}
QString CsSScheduleSendFiles::getUuid() const
{
    return uuid;
}

void CsSScheduleSendFiles::setUuid(const QString &value)
{
    uuid = value;
}
QString CsSScheduleSendFiles::getFileName() const
{
    return fileName;
}

void CsSScheduleSendFiles::setFileName(const QString &value)
{
    fileName = value;
}
QString CsSScheduleSendFiles::getDownUrl() const
{
    return downUrl;
}

void CsSScheduleSendFiles::setDownUrl(const QString &value)
{
    downUrl = value;
}
QString CsSScheduleSendFiles::getFileDestName() const
{
    return fileDestName;
}

void CsSScheduleSendFiles::setFileDestName(const QString &value)
{
    fileDestName = value;
}
QString CsSScheduleSendFiles::getSaveAbst() const
{
    return saveAbst;
}

void CsSScheduleSendFiles::setSaveAbst(const QString &value)
{
    saveAbst = value;
}
QString CsSScheduleSendFiles::getTaskUuid() const
{
    return taskUuid;
}

void CsSScheduleSendFiles::setTaskUuid(const QString &value)
{
    taskUuid = value;
}







