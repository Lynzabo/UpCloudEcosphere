#ifndef CSRUNSTRUCTSENDADDR_H
#define CSRUNSTRUCTSENDADDR_H

#include <QtCore>

/**
 * @brief The CsRUnstructSendAddr class 非结构化任务下发地址表
 * 存放非结构化任务下发节点服务器信息
 * 下发前【非结构化任务下发地址表】的"任务执行状态"值为0，代表未下发，下发时候修改该字段值为1，代表正在下发，
 * 节点服务器响应收到下发任务，修改该字段值为2，节点服务器下载完该任务中所有文件时候，修改该字段值，如果在当前
 * 下载策略下下载失败，修改该字段值为3，并在【非结构化任务下发状态表】存放每个出错文件错误描述，如果当前下载策
 * 略下下载成功，修改该字段值为4，【非结构化任务下发地址表】的“错误描述”在任何时段都存放着执行出错信息，如果上
 * 一操作失败，就不会有下一步操作。
 */

class CsRUnstructSendAddr
{
private:
    //UUID
    QString uuid;
    //节点服务地址UUID
    quint32 clientUuid;
    //任务执行状态
    QChar state;
    //错误描述
    QString error;
    //任务UUID
    quint32 taskUuid;
public:
    CsRUnstructSendAddr();

    QString getUuid() const;
    void setUuid(const QString &value);

    quint32 getClientUuid() const;
    void setClientUuid(const quint32 &value);

    QChar getState() const;
    void setState(const QChar &value);

    QString getError() const;
    void setError(const QString &value);

    quint32 getTaskUuid() const;
    void setTaskUuid(const quint32 &value);
};

#endif // CSRUNSTRUCTSENDADDR_H
