#ifndef TASKEXECMANAGER_H
#define TASKEXECMANAGER_H

#include <QtCore>
#include "util/taskExec/bean/taskinjson.h"
#include "util/taskExec/bean/taskoutjson.h"
#include "avro.h"
#include "base.h"

class TaskExecManager : public QThread
{
    Q_OBJECT
public:
    TaskExecManager();
    ~TaskExecManager();

    void init(const QString& taskName);

    void taskExec(void);
signals:
    //执行开始
    void evt_execBegin(const QString &taskName);
    //执行结束
    void evt_execEnd(const QString &taskName, const QString &result);
protected:
    void run();
private:
    //in
    QString m_taskName;
    TaskInJson m_taskInJson;

    //out
    QString m_result;
    TaskOutJson m_taskOutJson;

    //work process
    QProcess* m_process;
};

#endif // TASKEXECMANAGER_H
