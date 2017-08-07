#include "httpdownloadmanager.h"

HttpDownloadManager::HttpDownloadManager()
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

HttpDownloadManager::~HttpDownloadManager()
{
    clearAsyncFileMap();
    readyDownQueue->clear();
    delete readyDownQueue;
    delete subMutex;
//    qDebug() << "Destory HttpDownloadManager";
}

void HttpDownloadManager::download(const QMap<QString, QString> &upGroups, const bool &parallel, const int &_iisNum, const int &_downThreadsNum)
{
    transGroups = upGroups;
    this->iisNum = _iisNum;
    this->downThreadsNum = _downThreadsNum;
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
    emit
        start();
    startNextDownload();
}

void HttpDownloadManager::SubFileFinished(const QString &fKey)
{
    subMutex->lock();
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
    deleteMap(asyncFileMap,_fKey);
    //如果队列不为空，继续到startNextDownload申请下载
    if(readyDownQueue->size()==0 && notCompleteDownURLs.size() == 0 && downChecker== 0)
    {
        //发送所有文件下载完毕信号
//        qDebug() << "Download All File!";
        readyDownQueue->clear();
        emit
            end();
        blockStatus = false;
        subMutex->unlock();
    }
    else
    {
        subMutex->unlock();
        startNextDownload();
    }
}
void HttpDownloadManager::deleteMap(QMap<QString,FileDownThread*> &_asyncFileMap,const QString &_key)
{
    QMap<QString,FileDownThread*>::const_iterator i = _asyncFileMap.find(_key);

    FileDownThread* _fd = i.value();
    _asyncFileMap.remove(_key);
    delete _fd;

}
void HttpDownloadManager::SubFileDownloadError(const QString &fKey, const QString &errorStr)
{
    subMutex->lock();
    const QString _fKey = fKey;
    const QString _errorStr = errorStr;
    downChecker--;
    QString f_url = getKey2URL(_fKey);
    notCompleteDownURLs.removeOne(f_url);
    deleteMap(asyncFileMap,_fKey);
    emit
    error(f_url,_errorStr);
//    startNextDownload();
    if(readyDownQueue->size()==0 && notCompleteDownURLs.size() == 0 && downChecker== 0)
    {
        //发送所有文件下载完毕信号
//        qDebug() << "Download All File!";
        readyDownQueue->clear();
        emit
            end();
        blockStatus = false;
        subMutex->unlock();
    }
    else
    {
        subMutex->unlock();
        startNextDownload();
    }
}

void HttpDownloadManager::transProcess(const QString &fileUrl, const quint64 &haveDoneBytes, const quint64 &totalBytes)
{
    lockSize.lockForWrite();
    emit
        process(fileUrl,haveDoneBytes,totalBytes);
    lockSize.unlock();
}

void HttpDownloadManager::clearAsyncFileMap()
{
    foreach (FileDownThread * thread, this->asyncFileMap)
    {
//        thread->exit(0);
        delete thread;
    }
    this->asyncFileMap.clear();
}

void HttpDownloadManager::startNextDownload()
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
                goto blocking;
            //构建文件下载主键
            QString key = QUuid::createUuid().toString();
            //出队
            QString url = readyDownQueue->dequeue();
            FileDownThread *thread = new FileDownThread(key);
            QString abstPath = transGroups.value(url);

            //文件下载地址，和线程数
            thread->SetDownloadProp(url,abstPath,downThreadsNum);
            //获取当前文件下载进度信号槽
            connect(thread, SIGNAL(process(const QString &,const quint64 &,const quint64 &)),
                this, SLOT(transProcess(const QString &,const quint64 &,const quint64 &)),Qt::DirectConnection);
            //下载出错
            connect(thread, SIGNAL(FileDownloadError(const QString &,const QString &)),
                this, SLOT(SubFileDownloadError(const QString &,const QString &)),Qt::DirectConnection);
            //文件下载完成，自动回收当前线程
            connect(thread, SIGNAL(FileDownloadFinish(const QString &)),
                thread, SLOT(deleteLater()));
            //一个文件下载完毕信号槽
            connect(thread, SIGNAL(FileDownloadFinish(const QString &)),
                this, SLOT(SubFileFinished(const QString &)),Qt::DirectConnection);
            thread->start();
            //如果增加一个文件下载线程，增加线程数组，如果完成一个文件下载，减少这个线程数组
            asyncFileMap.insert(key,thread);
        }
    }
    else
    {}
    blocking:
    //阻塞主线程
    while(!blockStatus)
    {
        //qDebug() << "111";
    }
}

QString HttpDownloadManager::getKey2URL(const QString &fkey)
{
    QMap<QString,FileDownThread*>::const_iterator i = asyncFileMap.find(fkey);
    FileDownThread* _fd = i.value();
    if(_fd==NULL)
        return QString();
    QString f_url = _fd->getF_Url();
    return f_url;
}
QString HttpDownloadManager::getFileDownloadDestAbst(const QString &furl)
{
    QMap<QString,QString>::const_iterator i = transGroups.find(furl);
    QString _fd = i.value();
    return _fd;
}
