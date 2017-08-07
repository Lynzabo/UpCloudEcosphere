/**************************************************************************
**   UpCloudEcosphere
**   Copyright (c) UpCloud C/C++ development team.
**   All rights 2016 reserved.
**   Author : zhoujunying
**************************************************************************/

#include "upthread.h"
#include <stdio.h>
#include "ftp/ftpmeta.h"
UpThread::UpThread()
{

}
void UpThread::run()
{
   m_ftpPool->upload(m_files,false,false);
}
NetTransClient *UpThread::ftpPool() const
{
    return m_ftpPool;
}

void UpThread::setFtpPool(NetTransClient *ftpPool)
{
    m_ftpPool = ftpPool;
    connect(m_ftpPool,SIGNAL(start()),this,SLOT(on_start()));
    connect(m_ftpPool,SIGNAL(subFileEnd(const QString ,const QString ,const QString )),
            this,SLOT(on_subFileEnd(const QString ,const QString ,const QString )));
    connect(m_ftpPool,SIGNAL(end(const QString )),this,SLOT(on_end(const QString )));
    connect(m_ftpPool,SIGNAL(error(const QString ,const QString ,const QString )),
            this,SLOT(on_error(const QString ,const QString ,const QString )));
    connect(m_ftpPool,SIGNAL(process( QString ,quint64 , quint64 )),
            this,SLOT(on_process(QString,quint64,quint64)));
}
QMap<QString, QString> UpThread::files() const
{
    return m_files;
}

void UpThread::setFiles(const QMap<QString, QString> &files)
{
    m_files = files;
}

void UpThread::on_process(const QString &file, quint64 have, quint64 total)
{
    emit
    process(file,have,total);
}

void UpThread::on_start()
{
  emit
    startS();
}

void UpThread::on_subFileEnd(const QString &taskID, const QString &fileUrl, const QString &destAbst)
{
    emit
    subFileEnd(taskID,fileUrl,destAbst);
}

void UpThread::on_end(const QString &taskID)
{
    emit
    end(taskID);
}

void UpThread::on_error(const QString &taskID, const QString &src, const QString &errMsg)
{
    emit
    error(taskID,src,errMsg);
}
