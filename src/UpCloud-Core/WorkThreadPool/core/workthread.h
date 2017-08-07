#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QThread>
class QSemaphore;


class WorkThread : public QThread
{
    Q_OBJECT
public:
    WorkThread();
    ~WorkThread();

    enum State {
        Idle,
        Busy
    };

    State getCurrentState();
    void doWork();
signals:
    void taskArrive();
protected:
    void run();
private slots:
    void taskFinished();
private:
    QSemaphore* m_semaphore;
    bool m_isDestroy;
    State m_state;

};

#endif // WORKTHREAD_H
