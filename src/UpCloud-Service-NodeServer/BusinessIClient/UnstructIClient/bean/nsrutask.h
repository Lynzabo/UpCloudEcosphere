#ifndef NSRUNSTRUCTTASK_H
#define NSRUNSTRUCTTASK_H
#include <QtCore>
/**
 * @brief The NsRUnstructTask class 非结构化任务处理表
 * 任务状态代表任务状态，0代表废弃状态，1代表任务可用，2代表正在下载，3代表下载出错，4代表下载成功
 */
class NsRUnstructTask
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
    //添加时间
    QString insertTime;
public:
    NsRUnstructTask();

    QString getUuid() const;
    void setUuid(const QString &value);
    quint32 getTaskNum() const;
    void setTaskNum(const quint32 &value);
    quint16 getStrategy() const;
    void setStrategy(const quint16 &value);
    quint8 getState() const;
    void setState(const quint8 &value);
    QString getInsertTime() const;
    void setInsertTime(const QString &value);
};
#endif // NSRUNSTRUCTTASK_H
