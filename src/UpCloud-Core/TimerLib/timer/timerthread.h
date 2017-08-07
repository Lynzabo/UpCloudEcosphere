#ifndef TIMERTHREAD_H
#define TIMERTHREAD_H

#include <QThread>
#include "timerlib_global.h"

class TIMERLIBSHARED_EXPORT TimerThread : public QThread
{
    Q_OBJECT
public:
    TimerThread();
    ~TimerThread();

    void setTimeout(int msec);

    void timerStart();
    void timerStop();

    void timerDestroy();

signals:
    void evt_timeout();
protected:
    void run();
private:
    int m_timeout;
    bool m_isDestroy;
    bool m_isStop;
};

#endif // TIMERTHREAD_H
