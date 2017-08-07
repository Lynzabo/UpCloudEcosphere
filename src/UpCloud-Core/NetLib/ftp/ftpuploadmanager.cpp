#include "ftpuploadmanager.h"

FtpUploadManager::FtpUploadManager()
{
    readyUpQueue = new QQueue<QString>;
    readyUpQueue->clear();
    notCompleteUpURLs.clear();
    iisNum = 0;
    upThreadsNum = 0;
    clearAsyncFileMap();
    transGroups.clear();
    blockStatus = false;
    upChecker = 0;
    subMutex = new QMutex;
}

FtpUploadManager::~FtpUploadManager()
{
    clearAsyncFileMap();
    readyUpQueue->clear();
    delete subMutex;
}

void FtpUploadManager::upload(const QMap<QString, QString> &upGroups, const bool &parallel, FtpMeta *_meta, const int &_iisNum, const int &_upThreadsNum)
{
    meta = _meta;
    transGroups = upGroups;
    iisNum = _iisNum;
    upThreadsNum = _upThreadsNum;
    upChecker = upGroups.size();
    foreach (QString url, upGroups.keys())
    {
        QString *_tmpUrl = new QString;
        _tmpUrl->append(url.toLocal8Bit());
        notCompleteUpURLs.append(*_tmpUrl);
        readyUpQueue->enqueue(*_tmpUrl);
        delete _tmpUrl;
    }
    //TDODO 如果是同步上传,仅仅设置并发上传文件数就可以，如果是异步上传，上传数目使用默认的常量QUEUESIZE，以后从配置文件读取
    if(!parallel)
    {
        iisNum = 1;
    }
    QEventLoop loop;
    connect(this, SIGNAL(endloop()), &loop, SLOT(quit()));
    emit
    start();
    startNextUpload();
    loop.exec();
}

void FtpUploadManager::SubFileFinished(const QString &fKey)
{
    subMutex->lock();

    QMap<QString,FtpFileUpThread*>::const_iterator i = asyncFileMap.find(fKey);
    FtpFileUpThread* thread = i.value();
    qDebug()<<"wait begin"<<thread;
    thread->wait();
    qDebug()<<"wait ok"<<thread;

    const QString _fKey = fKey;
    upChecker--;
    QString f_abstpath = getKey2AbstPath(_fKey);
    if(!f_abstpath.isEmpty())
    {
        notCompleteUpURLs.removeOne(f_abstpath);
        QString destPath = getFileUploadDestAbst(f_abstpath);
        //一个文件上传完成信号
        emit
        subFileEnd(f_abstpath,destPath);
    }
    asyncFileMap.remove(fKey);
    delete thread;

    //如果readyUpQueue队列为空 and notCompleteUpURLs为空 and upChecker为空
    if(readyUpQueue->size()==0 && notCompleteUpURLs.size() == 0 && upChecker== 0)
    {
        //发送所有文件上传完毕信号
        readyUpQueue->clear();
        emit
        end();
        emit endloop();
        subMutex->unlock();
    }
    //如果队列不为空，继续到startNextUpnload申请上传
    else if(readyUpQueue->size()==0)
    {
        startNextUpload();
        subMutex->unlock();
    }
    else
    {
        subMutex->unlock();
    }
}
void FtpUploadManager::deleteMap(QMap<QString,FtpFileUpThread*> &_asyncFileMap,const QString &_key)
{
    if(_asyncFileMap.isEmpty())
        return;
    QMap<QString,FtpFileUpThread*>::const_iterator i = _asyncFileMap.find(_key);

    FtpFileUpThread* _fd = i.value();
    _asyncFileMap.remove(_key);
    delete _fd;

}
void FtpUploadManager::SubFileUploadError(const QString &fKey, const QString &errorStr)
{
    subMutex->lock();

    QMap<QString,FtpFileUpThread*>::const_iterator i = asyncFileMap.find(fKey);
    FtpFileUpThread* thread = i.value();
    thread->wait();

    const QString _fKey = fKey;
    const QString _errorStr = errorStr;
    upChecker--;
    QString f_abstpath = getKey2AbstPath(_fKey);
    notCompleteUpURLs.removeOne(f_abstpath);
    emit error(f_abstpath,_errorStr);

    asyncFileMap.remove(fKey);
    delete thread;

    //如果readyUpQueue队列为空 and notCompleteUpURLs为空 and upChecker为空
    if(readyUpQueue->size()==0 && notCompleteUpURLs.size() == 0 && upChecker== 0)
    {
        //发送所有文件上传完毕信号
        readyUpQueue->clear();
        emit
        end();
        emit endloop();
        subMutex->unlock();
    }
    //如果队列不为空，继续到startNextUpnload申请上传
    else if(readyUpQueue->size()==0)
    {
        startNextUpload();
        subMutex->unlock();
    }
    else
    {
        subMutex->unlock();
    }
}

void FtpUploadManager::transProcess(const QString &fileUrl, const quint64 &haveDoneBytes, const quint64 &totalBytes)
{
    lockSize.lockForWrite();
    emit
    process(fileUrl,haveDoneBytes,totalBytes);
    lockSize.unlock();
}

void FtpUploadManager::clearAsyncFileMap()
{
    foreach (FtpFileUpThread * thread, this->asyncFileMap)
    {
        delete thread;
    }
    this->asyncFileMap.clear();
}

void FtpUploadManager::startNextUpload()
{
    if(!readyUpQueue->isEmpty())
    {
        //如果允许同时上传的文件数目大于正在上传文件数，说明还可以分配上传节点，
        int length = 0;
        int asyLength = asyncFileMap.size();
        if(iisNum>asyLength)
        {
            length = iisNum-asyLength;
        }
        for(int i=0;i<length;i++)
        {
            if(readyUpQueue->isEmpty())
            {
                //goto blocking;
                break;
            }
            //构建文件上传主键
            QString key  = QUuid::createUuid().toString();
                //出队
            QString  abstPath = readyUpQueue->dequeue();
            QString  url= transGroups.value(abstPath);
            FtpFileUpThread *thread = new FtpFileUpThread(key);

            //文件上传地址，和线程数
            thread->SetUploadProp(abstPath, url,upThreadsNum,meta);
            //获取当前文件上传进度信号槽
            connect(thread, SIGNAL(process(const QString &,const quint64 &,const quint64 &)),
                    this, SLOT(transProcess(const QString &,const quint64 &,const quint64 &)),Qt::QueuedConnection);
            //上传出错
            connect(thread, SIGNAL(FileUploadError(const QString &,const QString &)),
                    this, SLOT(SubFileUploadError(const QString &,const QString &)),Qt::QueuedConnection);
            //一个文件上传完毕信号槽
            connect(thread, SIGNAL(FileUploadFinish(const QString &)),
                    this, SLOT(SubFileFinished(const QString &)),Qt::QueuedConnection);
            //如果增加一个文件上传线程，增加线程数组，如果完成一个文件上传，减少这个线程数组
            asyncFileMap.insert(key,thread);

            thread->start();
        }
    }
}

QString FtpUploadManager::getKey2AbstPath(const QString &fkey)
{
    QMap<QString,FtpFileUpThread*>::const_iterator i = asyncFileMap.find(fkey);
    FtpFileUpThread* _fd = i.value();
    if(_fd==NULL)
        return QString();
    QString f_abstpath = _fd->getF_AbstPath();
    return f_abstpath;
}
QString FtpUploadManager::getFileUploadDestAbst(const QString &furl)
{
    QMap<QString,QString>::const_iterator i = transGroups.find(furl);
    QString _fd = i.value();
    return _fd;
}
