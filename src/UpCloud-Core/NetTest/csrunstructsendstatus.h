#ifndef CSRUNSTRUCTSENDSTATUS_H
#define CSRUNSTRUCTSENDSTATUS_H

#include <QtCore>

/**
 * @brief The CsRUnstructSendStatus class 非结构化任务下发状态表
 * 非结构化任务下发出错信息情况
 * 任务在当前下载策略下，如果执行失败会在该表增加错误信息，如果成功不会增加数据。
 * 对于当前任务，只记录出错文件错误信息，成功的文件不记录。
 */

class CsRUnstructSendStatus
{

private:
    //UUID
    QString uuid;
    //节点服务地址UUID
    quint32 clientUuid;
    //下发文件表UUID
    quint32 sendFileUuid;
    //错误描述
    QString error;
    //任务UUID
    quint32 taskUuid;
public:
    CsRUnstructSendStatus();

    QString getUuid() const;
    void setUuid(const QString &value);

    quint32 getClientUuid() const;
    void setClientUuid(const quint32 &value);

    quint32 getSendFileUuid() const;
    void setSendFileUuid(const quint32 &value);

    QString getError() const;
    void setError(const QString &value);

    quint32 getTaskUuid() const;
    void setTaskUuid(const quint32 &value);
};

#endif // CSRUNSTRUCTSENDSTATUS_H
