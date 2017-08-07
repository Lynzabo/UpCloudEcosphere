#ifndef CSRSTRUCTSENDADDR_H
#define CSRSTRUCTSENDADDR_H

#include <QtCore>

/**
 * @brief The CsRStructSendAddr class 结构化任务下发地址表
 * 存放结构化任务下发节点服务器信息
 * 当下发时间到的时候，结构化扫描器会自动扫描并进行下发。下发前【结构化任务下发地址表】的"任务执行状态"值为0，代表未下发，
 * 下发时候修改该字段值为1，代表正在下发，并修改【结构化任务表】状态为2,节点服务器响应收到下发任务，修改该字段值为2，并修
 * 改【结构化任务表】状态为3，节点服务器下载完该任务中所有文件时候，修改该字段值，如果在当前执行策略下下载失败，修改该字段
 * 值为3，并在【结构化任务下发状态表】存放每个出错文件错误描述，并且修改【结构化任务表】的任务状态为4，注意，当为3的时候不
 * 用再次修改。如果当前执行策略下下载成功，修改该字段值为4，并且修改【结构化任务表】的任务状态为5（如果有节点出错，会自动修
 * 改为最新状态），在当前执行策略下解析出错，修改该字段值为5，并在【结构化任务下发状态表】存放每个出错文件错误描述，并且修改
 * 【结构化任务表】的任务状态为6，注意，当为5的时候不用再次修改。在当前策略下解析成功，修改该字段值为6，并且修改【结构化任务
 * 表】的任务状态为7。【结构化任务下发地址表】的“错误描述”在任何时段都存放着执行出错信息，如果上一操作失败，就不会有下一步操作。
 */


class CsRStructSendAddr
{

private:
    //UUID
    QString uuid;
    //节点服务地址UUID
    QString clientUuid;    
    //任务UUID
    QString taskUuid;
    //所属节点服务器组描述
    QString groupDesc;
public:
    CsRStructSendAddr();

    QString getUuid() const;
    void setUuid(const QString &value);

    QString getClientUuid() const;
    void setClientUuid(const QString &value);    

    QString getTaskUuid() const;
    void setTaskUuid(const QString &value);

    QString getGroupDesc() const;
    void setGroupDesc(const QString &value);
};

#endif // CSRSTRUCTSENDADDR_H
