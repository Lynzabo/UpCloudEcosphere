#ifndef CREATEFTPFILEINFO_H
#define CREATEFTPFILEINFO_H
#include "baseiserver.h"
#include "baseiserverlib_global.h"

class BASEISERVERLIBSHARED_EXPORT CreateFtpFileInfo
{
public:
    CreateFtpFileInfo();
    QString getFileName() const;
    void setFileName(const QString &value);

    QString getSaveAbst() const;
    void setSaveAbst(const QString &value);

    QString getSrcAbst() const;
    void setSrcAbst(const QString &value);

    QString getFileDestName() const;
    void setFileDestName(const QString &value);

    void setFtpInfo(const QString &name,const QString &savePath,const QString &srcPath);

    QString getHardAbst();

    QString getDownUrl();
private:
    QString fileName;
    QString saveAbst;
    QString srcAbst;
    QString fileDestName;

    QString ftpRoootPath;
    QString ftpAddr;
};

#endif // CREATEFTPFILEINFO_H
