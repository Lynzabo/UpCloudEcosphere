#include "workthread.h"
#include <QSemaphore>

WorkThread::WorkThread()
{
    m_semaphore = new QSemaphore;
    m_state = State::Idle;
    m_isDestroy = false;
}

WorkThread::~WorkThread()
{
    if(m_semaphore != NULL)
    {
        delete m_semaphore;
        m_semaphore = NULL;
    }
}

WorkThread::State WorkThread::getCurrentState()
{
    return m_state;
}

void WorkThread::run()
{
    while(m_isDestroy == false)
    {
        m_semaphore->acquire();
        emit taskArrive();
        m_state = State::Idle;
    }
}

void WorkThread::taskFinished()
{
    m_state = State::Idle;
}

void WorkThread::doWork()
{
    m_state = State::Busy;
    m_semaphore->release();
}
