#include "ftpdownloadmanager.h"
FtpDownloadManager::FtpDownloadManager()
{
    readyDownQueue = new QQueue<QString>;
    readyDownQueue->clear();
    notCompleteDownURLs.clear();
    iisNum = 0;
    downThreadsNum = 0;
    clearAsyncFileMap();
    transGroups.clear();
    blockStatus = false;
    downChecker = 0;
    subMutex = new QMutex;
}

FtpDownloadManager::~FtpDownloadManager()
{
    clearAsyncFileMap();
    readyDownQueue->clear();
    delete subMutex;
//    qDebug() << "Destory FtpDownloadManager";
}

void FtpDownloadManager::download(const QMap<QString, QString> &upGroups, const bool &parallel, FtpMeta *_meta, const int &_iisNum, const int &_downThreadsNum)
{
    meta = _meta;
    transGroups = upGroups;
    iisNum = _iisNum;
    downThreadsNum = _downThreadsNum;
    downChecker = upGroups.size();
    foreach (QString url, upGroups.keys())
    {
        QString *_tmpUrl = new QString;
        _tmpUrl->append(url.toLocal8Bit());
        notCompleteDownURLs.append(*_tmpUrl);
        readyDownQueue->enqueue(*_tmpUrl);
        delete _tmpUrl;
    }
    //TDODO 如果是同步下载,仅仅设置并发下载文件数就可以，如果是异步下载，下载数目使用默认的常量QUEUESIZE，以后从配置文件读取
    if(!parallel)
    {
        iisNum = 1;
    }
    QEventLoop loop;
    connect(this, SIGNAL(endloop()), &loop, SLOT(quit()));
    emit
    start();
    startNextDownload();
    loop.exec();
}



void FtpDownloadManager::SubFileFinished(const QString &fKey)
{
    subMutex->lock();

    QMap<QString,FtpFileDownThread*>::const_iterator i = asyncFileMap.find(fKey);
    FtpFileDownThread* thread = i.value();
    qDebug()<<"wait begin"<<thread;
    thread->wait();
    qDebug()<<"wait ok"<<thread;

    const QString _fKey = fKey;
    downChecker--;
    QString f_url = getKey2URL(_fKey);
    if(!f_url.isEmpty())
    {
        notCompleteDownURLs.removeOne(f_url);

        QString destPath = getFileDownloadDestAbst(f_url);
        //一个文件下载完成信号
        emit
        subFileEnd(f_url,destPath);
    }

    asyncFileMap.remove(fKey);
    delete thread;

    //如果readyDownQueue队列为空 and notCompleteDownURLs为空 and downChecker为空
    if(readyDownQueue->size()==0 && notCompleteDownURLs.size() == 0 && downChecker== 0)
    {
        //发送所有文件下载完毕信号
//        qDebug() << "Download All File!";
        readyDownQueue->clear();
        emit
        end();
        emit endloop();
        subMutex->unlock();

    }
    //如果队列不为空，继续到startNextDownload申请下载
    else if(readyDownQueue->size() > 0)
    {
        startNextDownload();
        subMutex->unlock();
    }
    else
    {
        subMutex->unlock();
    }
}
void FtpDownloadManager::deleteMap(QMap<QString,FtpFileDownThread*> &_asyncFileMap,const QString &_key)
{
    if(_asyncFileMap.isEmpty())
        return;
    QMap<QString,FtpFileDownThread*>::const_iterator i = _asyncFileMap.find(_key);

    FtpFileDownThread* _fd = i.value();
    _asyncFileMap.remove(_key);
    delete _fd;

}

void FtpDownloadManager::SubFileDownloadError(const QString &fKey, const QString &errorStr)
{
    subMutex->lock();

    QMap<QString,FtpFileDownThread*>::const_iterator i = asyncFileMap.find(fKey);
    FtpFileDownThread* thread = i.value();
    thread->wait();


    const QString _fKey = fKey;
    const QString _errorStr = errorStr;
    downChecker--;
    QString f_url = getKey2URL(_fKey);
    notCompleteDownURLs.removeOne(f_url);
    emit
    error(f_url,_errorStr);

    asyncFileMap.remove(fKey);
    delete thread;

    //    startNextDownload();
    if(readyDownQueue->size()==0 && notCompleteDownURLs.size() == 0 && downChecker== 0)
    {
        //发送所有文件下载完毕信号
        readyDownQueue->clear();
        emit
        end();
        emit endloop();
        subMutex->unlock();
    }
    else if(readyDownQueue->size() > 0)
    {
        startNextDownload();
        subMutex->unlock();
    }
    else
    {
        subMutex->unlock();
    }
}

void FtpDownloadManager::transProcess(const QString &fileUrl, const quint64 &haveDoneBytes, const quint64 &totalBytes)
{
    lockSize.lockForWrite();
    emit
    process(fileUrl,haveDoneBytes,totalBytes);
    lockSize.unlock();
}

void FtpDownloadManager::clearAsyncFileMap()
{
    foreach (FtpFileDownThread * thread, this->asyncFileMap)
    {
        delete thread;
    }
    this->asyncFileMap.clear();
}

void FtpDownloadManager::startNextDownload()
{
    if(!readyDownQueue->isEmpty())
    {
        //如果允许同时下载的文件数目大于正在下载文件数，说明还可以分配下载节点，
        int length = 0;
        int asyLength = asyncFileMap.size();
        if(iisNum>asyLength)
        {
            length = iisNum-asyLength;
        }
        for(int i=0;i<length;i++)
        {
            if(readyDownQueue->isEmpty())
            {
                //goto blocking;
                break;
            }
            //构建文件下载主键
            QString key = QUuid::createUuid().toString();
            //出队
            QString url = readyDownQueue->dequeue();
            FtpFileDownThread *thread = new FtpFileDownThread(key);
            QString abstPath = transGroups.value(url);
            qDebug() << "abstPath=" <<abstPath;

            //文件下载地址，和线程数
            thread->SetDownloadProp(url,abstPath,downThreadsNum,meta);

            //获取当前文件下载进度信号槽
            connect(thread, SIGNAL(process(const QString &,const quint64 &,const quint64 &)),
                    this, SLOT(transProcess(const QString &,const quint64 &,const quint64 &)),Qt::QueuedConnection);

            //下载出错
            connect(thread, SIGNAL(FileDownloadError(const QString &,const QString &)),
                    this, SLOT(SubFileDownloadError(const QString &,const QString &)),Qt::QueuedConnection);

            //一个文件下载完毕信号槽
            connect(thread, SIGNAL(FileDownloadFinish(const QString &)),
                    this, SLOT(SubFileFinished(const QString &)),Qt::QueuedConnection);

            //如果增加一个文件下载线程，增加线程数组，如果完成一个文件下载，减少这个线程数组
            asyncFileMap.insert(key,thread);

            thread->start();
        }
    }
}

QString FtpDownloadManager::getKey2URL(const QString &fkey)
{
    QMap<QString,FtpFileDownThread*>::const_iterator i = asyncFileMap.find(fkey);
    FtpFileDownThread* _fd = i.value();
    if(_fd==NULL)
        return QString();
    QString f_url = _fd->getF_Url();
    return f_url;
}
QString FtpDownloadManager::getFileDownloadDestAbst(const QString &furl)
{
    QMap<QString,QString>::const_iterator i = transGroups.find(furl);
    QString _fd = i.value();
    return _fd;
}
