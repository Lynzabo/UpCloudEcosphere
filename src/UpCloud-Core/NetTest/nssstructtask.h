#ifndef NSSSTRUCTTASK_H
#define NSSSTRUCTTASK_H
#include <QtCore>

/**
 * @brief The NsSStructTask class   结构化任务处理归档表
 * 任务状态代表任务状态，0代表废弃状态，1代表任务可用，2代表正在下载，3代表下载出错，4代表下载成功，5代表正在解析，6代表解析出错，7代表解析成功
 */
class NsSStructTask
{
private:
    //UUID
    QString uuid;
    //计划任务编号
    quint32 taskNum;
    //下发策略
    quint16 strategy;
    //任务状态
    QChar state;
    //任务执行时刻
    QString execTime;
    //添加时间
    QString insertTime;
public:
    NsSStructTask();

    QString getUuid() const;
    void setUuid(const QString &value);
    quint32 getTaskNum() const;
    void setTaskNum(const quint32 &value);
    quint16 getStrategy() const;
    void setStrategy(const quint16 &value);
    QChar getState() const;
    void setState(const QChar &value);
    QString getExecTime() const;
    void setExecTime(const QString &value);
    QString getInsertTime() const;
    void setInsertTime(const QString &value);
};

#endif // NSSSTRUCTTASK_H
