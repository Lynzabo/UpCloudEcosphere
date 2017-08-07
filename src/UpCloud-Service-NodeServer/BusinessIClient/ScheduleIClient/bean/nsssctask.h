#ifndef NSSSCHEDULETASK_H
#define NSSSCHEDULETASK_H
#include <QtCore>

/**
 * @brief The NsSScheduleTask class 控制传输任务处理归档表
 * 任务状态代表任务状态，0代表废弃状态，1代表任务可用，2代表正在下载，3代表下载出错，4代表下载成功，5代表正在运行，6代表运行出错，7代表运行成功
 */
class NsSScheduleTask
{
private:
    //UUID
    QString uuid;
    //计划任务编号
    quint32 taskNum;
    //下发策略
    quint16 strategy;
    //任务状态
    quint8 state;
    //任务执行时刻
    QString execTime;
    //入口文件保存路径
    QString saveAbst;
    //添加时间
    QString insertTime;
public:
    NsSScheduleTask();
    QString getUuid() const;
    void setUuid(const QString &value);
    quint32 getTaskNum() const;
    void setTaskNum(const quint32 &value);
    quint16 getStrategy() const;
    void setStrategy(const quint16 &value);
    quint8 getState() const;
    void setState(const quint8 &value);
    QString getExecTime() const;
    void setExecTime(const QString &value);
    QString getSaveAbst() const;
    void setSaveAbst(const QString &value);
    QString getInsertTime() const;
    void setInsertTime(const QString &value);
};

#endif // NSSSCHEDULETASK_H
