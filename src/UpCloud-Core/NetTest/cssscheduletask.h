#ifndef CSSSCHEDULETASK_H
#define CSSSCHEDULETASK_H

#include <QtCore>

/**
 * @brief The CsSScheduleTask class 控制传输任务归档表
 * 任务状态代表任务状态，0代表废弃状态，1代表可用，2代表正在下发，3代表已经下发，4代表所有节点服务器下载数据文件时候有出错，
 * 5代表所有节点服务下载都已成功，6代表所有节点服务器解析数据文件有出错，7代表所有节点服务器解析数据文件都成功。
 * 执行策略包括下载策略和数据文件解析策略
 */
class CsSScheduleTask
{

private:
    //UUID
    QString uuid;
    //任务名称
    QString taskName;
    //计划任务编号
    quint32 taskNum;
    //任务描述
    QString description;
    //任务下发时间
    QString sendTime;
    //任务执行时刻
    QString execTime;
    //执行策略
    quint16 strategy;
    //任务状态
    QChar state;
    //入口文件保存路径
    QString saveAbst;
    //添加人
    QString insertor;
    //添加时间
    QString insertTime;
    //操作人
    QString operater;
    //操作时间
    QString operaTime;
public:
    CsSScheduleTask();

    QString getUuid() const;
    void setUuid(const QString &value);

    QString getTaskName() const;
    void setTaskName(const QString &value);

    quint32 getTaskNum() const;
    void setTaskNum(const quint32 &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QString getSendTime() const;
    void setSendTime(const QString &value);

    QString getExecTime() const;
    void setExecTime(const QString &value);

    quint16 getStrategy() const;
    void setStrategy(const quint16 &value);

    QChar getState() const;
    void setState(const QChar &value);

    QString getSaveAbst() const;
    void setSaveAbst(const QString &value);

    QString getInsertor() const;
    void setInsertor(const QString &value);

    QString getInsertTime() const;
    void setInsertTime(const QString &value);

    QString getOperater() const;
    void setOperater(const QString &value);

    QString getOperaTime() const;
    void setOperaTime(const QString &value);
};

#endif // CSSSCHEDULETASK_H
