#ifndef NSRSCHEDULESENDFILES_H
#define NSRSCHEDULESENDFILES_H
#include <QtCore>

/**
 * @brief The NsRScheduleSendFiles class    控制传输任务下发文件处理表
 * 存放控制传输任务下发文件
 * 状态0代表未下载，1代表下载出错，2代表下载成功，3代表入口文件执行出错，4代表入口文件执行成功
 */
class NsRScheduleSendFiles
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
    QString state;
    //错误信息
    QString error;

public:
    NsRScheduleSendFiles();
    QString getUuid() const;
    void setUuid(const QString &value);
    QString getFileUrl() const;
    void setFileUrl(const QString &value);
    QString getFileAbst() const;
    void setFileAbst(const QString &value);
    QString getTaskUuid() const;
    void setTaskUuid(const QString &value);
    QString getState() const;
    void setState(const QString &value);
    QString getError() const;
    void setError(const QString &value);
};

#endif // NSRSCHEDULESENDFILES_H
