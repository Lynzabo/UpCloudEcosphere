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
    QString clientUuid;
    //下发文件表UUID
    QString sendFileUuid;
    //错误描述
    QString error;
    //任务UUID
    QString taskUuid;
    //文件状态
    quint8 state;
    //下发地址表UUID
    QString sendAddrUuid;
public:
    CsRUnstructSendStatus();

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

    quint8 getState() const;
    void setState(const quint8 &value);

    QString getSendAddrUuid() const;
    void setSendAddrUuid(const QString &value);
};

#endif // CSRUNSTRUCTSENDSTATUS_H
