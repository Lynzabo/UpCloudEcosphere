#ifndef NSRUNSTRUCTSENDFILES_H
#define NSRUNSTRUCTSENDFILES_H
#include <QtCore>

/**
 * @brief The NsRUnstructSendFiles class    非结构化任务下发文件处理表
 * 存放非结构化任务下发文件
 * 状态0代表未下载，1代表下载出错，2代表下载成功。当出错的时候，ERROR字段填写错误信息，当下载成功或者未下载，ERROR字段为空
 */
class NsRUnstructSendFiles
{
private:
    //UUID
    QString uuid;
    //文件下载地址
    QString fileUrl;
    //文件保存路径
    QString fileAbst;
    //任务UUID
    QString taskUuid;
    //状态
    quint8 state;
    //错误信息
    QString error;
public:
    NsRUnstructSendFiles();
    QString getUuid() const;
    void setUuid(const QString &value);
    QString getFileUrl() const;
    void setFileUrl(const QString &value);
    QString getFileAbst() const;
    void setFileAbst(const QString &value);
    QString getTaskUuid() const;
    void setTaskUuid(const QString &value);
    quint8 getState() const;
    void setState(const quint8 &value);
    QString getError() const;
    void setError(const QString &value);
};


#endif // NSRUNSTRUCTSENDFILES_H
