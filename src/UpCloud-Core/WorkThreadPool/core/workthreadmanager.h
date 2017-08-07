#ifndef WORKTHREADMANAGER_H
#define WORKTHREADMANAGER_H

#include <QQueue>
#include <QtGlobal>
#include <QThread>
#include "workthreadpool_global.h"
class QMutex;
class WorkThread;

class WORKTHREADPOOLSHARED_EXPORT WorkThreadManager : public QThread
{
    Q_OBJECT
public:
    WorkThreadManager();
    ~WorkThreadManager();

    void setThreadCount(int threadCount);

    void workStart();
    void workStop();

    void workDestroy();

public:
    QList<WorkThread*> m_threadList;

private slots:
    void do_Timeout();
    void scheduleTask();

protected:
    void run();

private:
    QMutex* m_mutex;
    QQueue<int> m_queue;
    bool m_isStop;
};

#endif // WORKTHREADMANAGER_H
