#include "downthread.h"
#include <stdio.h>
#include "ftp/ftpmeta.h"
DownThread::DownThread()
{

}

void DownThread::run()
{
   m_ftpPool->download(m_files,true,false);
}
NetTransClient *DownThread::ftpPool() const
{
    return m_ftpPool;
}

void DownThread::setFtpPool(NetTransClient *ftpPool)
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
QMap<QString, QString> DownThread::files() const
{
    return m_files;
}

void DownThread::setFiles(const QMap<QString, QString> &files)
{
    m_files = files;
}

void DownThread::on_process(const QString &file, quint64 have, quint64 total)
{
    emit
    process(file,have,total);
}

void DownThread::on_start()
{
  emit
    startS();
}

void DownThread::on_subFileEnd(const QString &taskID, const QString &fileUrl, const QString &destAbst)
{
    emit
    subFileEnd(taskID,fileUrl,destAbst);
}

void DownThread::on_end(const QString &taskID)
{
    emit
    end(taskID);
}

void DownThread::on_error(const QString &taskID, const QString &src, const QString &errMsg)
{
    emit
    error(taskID,src,errMsg);
}



