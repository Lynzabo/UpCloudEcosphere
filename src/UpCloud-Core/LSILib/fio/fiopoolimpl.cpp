/**************************************************************************
**   UpCloudEcosphere
**   Copyright (c) UpCloud C/C++ development team.
**   All rights 2016 reserved.
**   Author : dyk
**************************************************************************/

#include "fiopoolimpl.h"
#include "fio/del/delpool.h"

FIOPoolImpl::FIOPoolImpl()
{
    m_delPool = NULL;
}

FIOPoolImpl::~FIOPoolImpl()
{
    if(m_delPool != NULL)
    {
        delete m_delPool;
        m_delPool = NULL;
    }
}

void FIOPoolImpl::del(const QList<QString> &posNames, const quint32 asyncCount)
{
    m_delPool = new DelPool;
    m_delPool->init(posNames, asyncCount);
    connect(m_delPool, SIGNAL(evt_IOBegin()), this, SIGNAL(evt_IOBegin()), Qt::QueuedConnection);
    connect(m_delPool, SIGNAL(evt_IOEnd()), this, SIGNAL(evt_IOEnd()), Qt::QueuedConnection);
    connect(m_delPool, SIGNAL(evt_IOProcess(quint32)), this, SIGNAL(evt_IOProcess(quint32)), Qt::QueuedConnection);
    connect(m_delPool, SIGNAL(evt_IOOneFileEnd(QString)), this, SIGNAL(evt_IOOneFileEnd(QString)), Qt::QueuedConnection);
    connect(m_delPool, SIGNAL(evt_IOOneFileError(QString,QString)), this, SIGNAL(evt_IOOneFileError(QString,QString)), Qt::QueuedConnection);
    m_delPool->del();
}

QList<QString> FIOPoolImpl::dir(const QString &dirName)
{
    //TODO
    QList<QString> tmp;
    return tmp;
}

void FIOPoolImpl::replace(const QMap<QString, QString> &posNames)
{
    //TODO
}

void FIOPoolImpl::rename(const QMap<QString, QString> &posNames)
{
    //TODO
}

