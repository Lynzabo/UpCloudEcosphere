#ifndef TASKEXECPOOLIMPL_H
#define TASKEXECPOOLIMPL_H

#include "taskexecpool.h"
#include "util/taskExec/taskexecmanager.h"


class TaskExecPoolImpl : public TaskExecPool
{
    Q_OBJECT
public:
    TaskExecPoolImpl();
    ~TaskExecPoolImpl();

    void init(const QString &taskName);
    void taskExec(void);
protected slots:
    void on_execBegin(const QString &taskName);
    void on_execEnd(const QString& taskName, const QString &result);
private:
    TaskExecManager* m_taskExecManager;
};

#endif // TASKEXECPOOLIMPL_H
