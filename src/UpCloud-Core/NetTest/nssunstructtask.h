#ifndef NSSUNSTRUCTTASK_H
#define NSSUNSTRUCTTASK_H
#include <QtCore>
/**
 * @brief The NsSUnstructTask class 非结构化任务处理归档表
 * 任务状态代表任务状态，0代表废弃状态，1代表任务可用，2代表正在下载，3代表下载出错，4代表下载成功
 */
class NsSUnstructTask
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
    //添加时间
    QString insertTime;
public:
    NsSUnstructTask();

    QString getUuid() const;
    void setUuid(const QString &value);
    quint32 getTaskNum() const;
    void setTaskNum(const quint32 &value);
    quint16 getStrategy() const;
    void setStrategy(const quint16 &value);
    QChar getState() const;
    void setState(const QChar &value);
    QString getInsertTime() const;
    void setInsertTime(const QString &value);
};

#endif // NSSUNSTRUCTTASK_H
