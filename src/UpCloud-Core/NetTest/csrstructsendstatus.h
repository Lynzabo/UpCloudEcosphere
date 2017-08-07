#ifndef CSRSTRUCTSENDSTATUS_H
#define CSRSTRUCTSENDSTATUS_H

#include <QtCore>

/**
 * @brief The CsRStructSendStatus class 结构化任务执行状态表
 * 结构化任务下发出错信息情况
 * 任务在当前执行策略下，如果执行失败会在该表增加错误信息，如果成功不会增加数据。该错误会根据执行策略记录，
 * 可能在有文件下载出错，有文件下载成功时候记录该文件解析出错信息。对于当前任务，只记录出错文件错误信息，成功的文件不记录。
 */


class CsRStructSendStatus
{

private:
    //UUID
    QString uuid;
    //节点服务地址UUID
    QString clientUuid;
    //下发文件表UUID
    QString sendFileUuid;
    //错误描述
    QString error;
    //任务UUID
    QString taskUuid;
public:
    CsRStructSendStatus();

    QString getUuid() const;
    void setUuid(const QString &value);

    QString getClientUuid() const;
    void setClientUuid(const QString &value);

    QString getSendFileUuid() const;
    void setSendFileUuid(const QString &value);

    QString getError() const;
    void setError(const QString &value);

    QString getTaskUuid() const;
    void setTaskUuid(const QString &value);
};

#endif // CSRSTRUCTSENDSTATUS_H
