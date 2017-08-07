#ifndef DTASK_H
#define DTASK_H

#include <QtCore>
/**
 * @brief The DTask class   任务信息    与WEB交互数据实体
 */
class DTask
{
public:
    DTask();
    QString getTaskName() const;
    void setTaskName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    quint16 getStrategy() const;
    void setStrategy(const quint16 &value);

private:
    QString taskName;
    QString description;
    quint16 strategy;

};

#endif // DTASK_H
