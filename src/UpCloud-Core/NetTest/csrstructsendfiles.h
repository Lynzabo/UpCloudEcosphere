#ifndef CSRSTRUCTSENDFILES_H
#define CSRSTRUCTSENDFILES_H

#include <QtCore>

/**
 * @brief The CsRStructSendFiles class 结构化任务下发文件表
 * 存放结构化下发任务文件
 * 文件有先后次序区别
 */
class CsRStructSendFiles
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
    //文件解析次序
    quint32 sequence;
    //任务UUID
    QString taskUuid;
public:
    CsRStructSendFiles();

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

    quint32 getSequence() const;
    void setSequence(const quint32 &value);

    QString getTaskUuid() const;
    void setTaskUuid(const QString &value);
};

#endif // CSRSTRUCTSENDFILES_H
