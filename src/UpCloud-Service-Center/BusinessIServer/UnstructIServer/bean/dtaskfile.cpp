#include "dtaskfile.h"

DTaskFile::DTaskFile()
{

}
QString DTaskFile::getFileName() const
{
    return fileName;
}

void DTaskFile::setFileName(const QString &value)
{
    fileName = value;
}
QString DTaskFile::getSrcAbst() const
{
    return srcAbst;
}

void DTaskFile::setSrcAbst(const QString &value)
{
    srcAbst = value;
}
QString DTaskFile::getFileDestName() const
{
    return fileDestName;
}

void DTaskFile::setFileDestName(const QString &value)
{
    fileDestName = value;
}
QString DTaskFile::getSaveAbst() const
{
    return saveAbst;
}

void DTaskFile::setSaveAbst(const QString &value)
{
    saveAbst = value;
}





