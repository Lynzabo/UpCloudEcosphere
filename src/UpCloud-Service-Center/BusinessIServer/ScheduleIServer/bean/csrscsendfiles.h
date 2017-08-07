#ifndef CSRSCHEDULESENDFILES_H
#define CSRSCHEDULESENDFILES_H

#include <QtCore>
/**
 * @brief The CsRScheduleSendFiles class 控制传输下发文件表
 * 存放控制传输下发任务文件
 */

class CsRScheduleSendFiles
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
    //文件硬链接地址
    QString hardAbst;
    //文件来源
    quint8 fileSrc;
public:
    CsRScheduleSendFiles();

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
    QString getHardAbst() const;
    void setHardAbst(const QString &value);
    quint8 getFileSrc() const;
    void setFileSrc(const quint8 &value);
};

#endif // CSRSCHEDULESENDFILES_H
