#ifndef NSRSTRUCTSENDFILES_H
#define NSRSTRUCTSENDFILES_H
#include <QtCore>

/**
 * @brief The NsRStructSendFiles class  结构化任务下发文件处理表
 * 存放结构化任务下发文件
 * 状态0代表未下载，1代表下载出错，2代表下载成功，3代表解析出错，4代表解析成功
 */
class NsRStructSendFiles
{
private:
    //UUID
    QString uuid;
    //文件下载地址
    QString fileUrl;
    //文件保存路径
    QString fileAbst;
    //文件解析次序
    quint32 sequence;
    //任务UUID
    QString taskUuid;
    //状态
    QChar state;
    //错误信息
    QString error;
public:
    NsRStructSendFiles();
    QString getUuid() const;
    void setUuid(const QString &value);
    QString getFileUrl() const;
    void setFileUrl(const QString &value);
    QString getFileAbst() const;
    void setFileAbst(const QString &value);
    quint32 getSequence() const;
    void setSequence(const quint32 &value);
    QString getTaskUuid() const;
    void setTaskUuid(const QString &value);
    QChar getState() const;
    void setState(const QChar &value);
    QString getError() const;
    void setError(const QString &value);
};

#endif // NSRSTRUCTSENDFILES_H
