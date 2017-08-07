#include "fileblockdownloadthread.h"

FileBlockDownloadThread::FileBlockDownloadThread(int index): m_Index(index)
{
    moveToThread(this);
    m_HaveDoneBytes = 0;
    m_StartPoint = 0;
    m_EndPoint = 0;
    m_File = NULL;
}

FileBlockDownloadThread::~FileBlockDownloadThread()
{
//    qDebug() << "Destory FileBlockDownloadThread";
//    delete m_File;
}

void FileBlockDownloadThread::SetDownloadProp(const QUrl &url, QFile *file, quint64 startPoint, quint64 endPoint)
{
    if( NULL == file )
            return;
    m_Url = url;
    m_HaveDoneBytes = 0;
    m_StartPoint = startPoint;
    m_EndPoint = endPoint;
    m_File = file;
    m_FileName = file->fileName();
}

void FileBlockDownloadThread::run()
{
    QNetworkRequest qheader;
    qheader.setUrl(m_Url);

    QString range;
    range.sprintf("bytes=%lld-%lld", m_StartPoint, m_EndPoint);
    qheader.setRawHeader("User-Agent", "MyOwnBrowser 1.0");
    qheader.setRawHeader("Range",range.toLatin1());

    _manager = new QNetworkAccessManager();
    //开启一个事件循环
    reply = _manager->get(qheader);

/*
    connect(currentDownload, SIGNAL(downloadProgress(qint64,qint64)),
            SLOT(downloadProgress(qint64,qint64)));
            */
    //下载并写入文件块
    connect(reply, SIGNAL(readyRead()),SLOT(downloadReadyRead()));
    //文件块下载完成
    connect(reply, SIGNAL(finished()),this, SLOT(replyFinished()));
    //文件块下载完成，自动回收当前线程
    connect(reply, SIGNAL(finished()),this, SLOT(deleteLater()));
    this->exec();
}

void FileBlockDownloadThread::downloadReadyRead()
{
    if(reply->bytesAvailable()>0)
    {
        QByteArray buffer = reply->readAll();
        quint64 pos = m_StartPoint+m_HaveDoneBytes;
        emit
            ReadBlocks(buffer,pos);
        m_HaveDoneBytes +=buffer.size();

        QString path;
        path.append(QString("%1-tmp-%2.txt").arg(m_FileName).arg(m_Index));
        QFile outFile(path);
        outFile.open(QIODevice::WriteOnly);
        QTextStream ts(&outFile);
        ts << (m_StartPoint+m_HaveDoneBytes);
        outFile.close();
        int size = buffer.size();
        emit
            readIOBytes(size);
//        qDebug() << "\nQThread:" <<this->m_Index << ",m_StartPoint:" << m_StartPoint <<",m_HaveDoneBytes:" << m_HaveDoneBytes <<",m_EndPoint:"<<m_EndPoint;//bytesTotal为m_FileSize-m_StartPoint
    }
}

void FileBlockDownloadThread::replyFinished()
{
    if (reply->error()) {
            emit
                BlockDownloadError(m_Index,reply->errorString());
                return;
    } else {
        //printf("Succeeded.\n");
    }
    //删除临时文件
    QString path;
    path.append(QString("%1-tmp-%2.txt").arg(m_FileName).arg(m_Index));
    QFile::remove(path);
        //发射块下载完毕信号
        emit
            blockDownloadFinished(m_Index);
}
