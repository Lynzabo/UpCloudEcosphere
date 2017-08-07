#ifndef CSSUNSTRUCTSENDFILES_H
#define CSSUNSTRUCTSENDFILES_H

#include <QtCore>

/**
 * @brief The CsSUnstructSendFiles class 非结构化任务下发文件归档表
 * 存放非结构化下发任务文件
 */

class CsSUnstructSendFiles
{

private:
    //UUID
    QString uuid;
    //原文件名
    QString fileName;
    //文件下载地址
    QString downUrl;
    //新文件名
    QString fileDestName;
    //文件保存路径
    QString saveAbst;
    //任务UUID
    QString taskUuid;
public:
    CsSUnstructSendFiles();

    QString getUuid() const;
    void setUuid(const QString &value);

    QString getFileName() const;
    void setFileName(const QString &value);

    QString getDownUrl() const;
    void setDownUrl(const QString &value);

    QString getFileDestName() const;
    void setFileDestName(const QString &value);

    QString getSaveAbst() const;
    void setSaveAbst(const QString &value);

    QString getTaskUuid() const;
    void setTaskUuid(const QString &value);
};

#endif // CSSUNSTRUCTSENDFILES_H
