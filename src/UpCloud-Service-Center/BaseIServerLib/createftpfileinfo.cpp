#include "createftpfileinfo.h"

CreateFtpFileInfo::CreateFtpFileInfo()
{
    //[6].1 获取Ftp根目录
    ftpRoootPath.clear();
    ftpAddr;ftpAddr.clear();

    ServerConf serverConf;
    serverConf.getFtpRootPath(ftpRoootPath);
    serverConf.getFtpAddr(ftpAddr);
}

QString CreateFtpFileInfo::getFileName() const
{
    return fileName;
}

void CreateFtpFileInfo::setFileName(const QString &value)
{
    fileName = value;
}

QString CreateFtpFileInfo::getSaveAbst() const
{
    return saveAbst;
}

void CreateFtpFileInfo::setSaveAbst(const QString &value)
{
    saveAbst = value;
}

QString CreateFtpFileInfo::getSrcAbst() const
{
    return srcAbst;
}

void CreateFtpFileInfo::setSrcAbst(const QString &value)
{
    srcAbst = value;
}

void CreateFtpFileInfo::setFtpInfo(const QString &name, const QString &savePath, const QString &srcPath)
{
    fileName = name;
    saveAbst = savePath;
    srcAbst = srcPath;
}

QString CreateFtpFileInfo::getHardAbst()
{
//    QString completeSuffix = QFileInfo(srcAbst).completeSuffix();
    QString hardAbst = ftpRoootPath + "/" + fileName;
    return hardAbst;
}

QString CreateFtpFileInfo::getDownUrl()
{
    QString downUrl = ftpAddr + fileName;
    return downUrl;
}

QString CreateFtpFileInfo::getFileDestName() const
{
    return fileDestName;
}

void CreateFtpFileInfo::setFileDestName(const QString &value)
{
    fileDestName = value;
}

