#include "workthreadmanager.h"
#include "workthread.h"
#include <QList>
#include <QThread>
#include <QMutex>


WorkThreadManager::WorkThreadManager()
{
    m_isStop = true;
    m_mutex = new QMutex;
    qDeleteAll(m_threadList);
    m_threadList.clear();
}

WorkThreadManager::~WorkThreadManager()
{
    if(m_mutex != NULL)
    {
        delete m_mutex;
        m_mutex = NULL;
    }
    qDeleteAll(m_threadList);
    m_threadList.clear();
}


void WorkThreadManager::run()
{
    this->exec();
}

void WorkThreadManager::scheduleTask()
{
    if(m_isStop == false)
    {
        while(m_queue.size())
        {
            int i = 0;
            for(i=0; i<m_threadList.size(); i++)
            {
                if(m_threadList.at(i)->getCurrentState() == WorkThread::Idle)
                {
                    m_queue.dequeue();
                    m_threadList.at(i)->doWork();
                    break;
                }
            }
            if(i== m_threadList.size())
            {
                break;
            }
        }
    }
}


void WorkThreadManager::setThreadCount(int threadCount)
{
    for(int i=0; i<threadCount; i++)
    {
        WorkThread* pwth = new WorkThread;
        pwth->start();
        m_threadList.append(pwth);
    }
}

void WorkThreadManager::workStart()
{
    m_isStop = false;
}

void WorkThreadManager::workStop()
{
    m_isStop = true;
}

void WorkThreadManager::workDestroy()
{
    this->quit();
}

void WorkThreadManager::do_Timeout()
{
    m_mutex->lock();
    m_queue.enqueue(0);
    this->scheduleTask();
    m_mutex->unlock();
}



