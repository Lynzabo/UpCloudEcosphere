#include "timerthread.h"

TimerThread::TimerThread()
{
    m_timeout = 0;
    m_isDestroy = false;
    m_isStop = true;
}

TimerThread::~TimerThread()
{
    m_timeout = 0;
    m_isDestroy = false;
    m_isStop = true;
}

void TimerThread::setTimeout(int msec)
{
    m_timeout = msec;
}

void TimerThread::run()
{
    while(m_isDestroy == false)
    {
        QThread::msleep(m_timeout);
        if(m_isStop == false)
        {
            emit evt_timeout();
        }
    }
}

void TimerThread::timerStop()
{
    m_isStop = true;
}


void TimerThread::timerStart()
{
    m_isStop = false;
}

void TimerThread::timerDestroy()
{
    m_isDestroy = true;
    this->quit();
}

