#include "filedownthread.h"
FileDownThread::FileDownThread(const QString &index)
{
    //一定不要加moveToThread
    //    moveToThread(this);
    f_Key = index;
    f_File = new QFile;
//    qDeleteAll(threadsVector);
    threadsVector.clear();
    f_ReceiveSize = 0;
    lock = new QReadWriteLock;
    lockSize = new QReadWriteLock;
}

FileDownThread::~FileDownThread()
{
    qDeleteAll(threadsVector);
    threadsVector.clear();
    delete lock;
    delete lockSize;
    //    delete f_File;
    //    qDebug() << "Destory FileDownThread";
}

void FileDownThread::SetDownloadProp(const QString &url, const QString &abstPath, const int &subAyncsSize)
{
    f_Url = url;
    f_SubAyncsSize = subAyncsSize;
    f_AbstPath = abstPath;
}

void FileDownThread::run()
{
    //普通单个文件下载
    //保存目录不存在，创建保存目录
    QFileInfo fileInfo(f_AbstPath);
    QString directory = fileInfo.absolutePath();
    QDir dir(directory);
    if(!dir.exists())
        dir.mkpath(directory);
    //如果目录没有创建成功，提示错误
    if(!dir.exists())
    {
        emit
        FileDownloadError(f_Key,QString("Save Path %1 is error").arg(f_AbstPath));
        return;
    }
    ////判断文件是否存在，如果存在就读取本地文件的大小和中心服务器上此文件的大小做比较，
    /// 如果大小一致，就不下载此文件，否则再继续下载此文件
    if(fileInfo.exists())
    {
        qint64 localSize = fileInfo.size();
        if((quint64)localSize >= f_FileSize)
        {
            //进度条显示
            emit
            process(f_Url,f_ReceiveSize,f_FileSize);
            //状态显示
            emit
            FileDownloadFinish(f_Key);
            return;
        }
    }

    f_FinishedNum = 0;
    f_URL = QUrl(f_Url);
    f_FileSize = GetFileSize(f_URL);
    if(f_FileSize==0)
    {
        emit
        FileDownloadError(f_Key,QString("Download link is invalid:%1").arg(f_Url));
        return;
    }
    QString fileName = f_AbstPath;
    //    //先获得文件的名字
    //    QFileInfo fileInfo(f_URL.path());
    //    QString fileName = fileInfo.fileName();
    if (fileName.isEmpty())
    {
        emit
        FileDownloadError(f_Key,QString("File Name is Empty\n%1").arg(f_Url));
        return;
    }
    else
    {
        f_File->setFileName(fileName);

        //打开文件
        f_File->open(QIODevice::WriteOnly | QIODevice::Append);
        for(int i=0; i<f_SubAyncsSize; i++)
        {
            //先算出每段的开头和结尾（HTTP协议所需要的信息）
            quint64 start = 0;
            quint64 begin = f_FileSize * i / f_SubAyncsSize;
            quint64 end = f_FileSize * (i+1) / f_SubAyncsSize;
            //读取断点位置
            QString path;
            path.append(QString("%1-tmp-%2.txt").arg(fileName).arg(i+1));
            QFile outFile(path);
            if(outFile.exists())
            {
                outFile.open(QIODevice::ReadOnly | QIODevice::Text);
                outFile.seek(0);
                start = QString(outFile.readAll()).toLong();
                outFile.close();
            }
            if(start==0 || start > end)
                start = begin;
            //读取上次断点续传的文件大小
            f_ReceiveSize = f_ReceiveSize+(start-begin);
            //分段下载该文件
            FileBlockDownloadThread *tempBlockThread = new FileBlockDownloadThread(i+1);
            //文件块传输
            connect(tempBlockThread, SIGNAL(ReadBlocks(const QByteArray &,const quint64 &)),
                    this, SLOT(WriteBlocks(const QByteArray &,const quint64 &)),Qt::DirectConnection);
            //下载出错
            connect(tempBlockThread, SIGNAL(BlockDownloadError(const int &,const QString &)),
                    this, SLOT(SubBlockDownloadError(const int &,const QString &)),Qt::DirectConnection);
            //文件块下载完毕
            connect(tempBlockThread, SIGNAL(blockDownloadFinished(int)),
                    this, SLOT(SubPartFinished(int)),Qt::DirectConnection);
            connect(tempBlockThread, SIGNAL(readIOBytes(int)),
                    this, SLOT(writeIOBytes(int)),Qt::DirectConnection);
            //设置当前线程下载文件块属性
            tempBlockThread->SetDownloadProp(f_URL, f_File, start, end);
            tempBlockThread->start();
            //            this->exec();///////
            this->threadsVector.append(tempBlockThread);
        }
    }
}

void FileDownThread::writeIOBytes(int size)
{
    if(lock!=NULL)
    {
        lockSize->lockForWrite();
        f_ReceiveSize = f_ReceiveSize+size;
        //    qDebug() << "DownloadSIZE:" << f_File->fileName()<< ","  << size <<"," << f_ReceiveSize << "," << f_FileSize;
        emit
        process(f_Url,f_ReceiveSize,f_FileSize);
        lockSize->unlock();
    }
}

void FileDownThread::SubBlockDownloadError(const int &index, const QString &errorStr)
{
    //    qDebug() << "fKey:" << f_Key << ",index:" << index << "errorStr:" << errorStr;
    emit
    FileDownloadError(f_Key,QString("File %1 's block %2 download error is %3\n").arg(f_Url).arg(index).arg(errorStr));
}

void FileDownThread::SubPartFinished(int index)
{
    f_FinishedNum++;
    //    qDebug() << "SubPartFinished";
    //如果完成数等于文件段数，则说明文件下载完毕，关闭文件，发生信号
    if( f_FinishedNum == f_SubAyncsSize )
    {
        f_File->close();
        this->threadsVector.clear();
        emit
        FileDownloadFinish(f_Key);

        //        qDebug() << "Download finished";
    }
}

void FileDownThread::WriteBlocks(const QByteArray &buffer, const quint64 &pos)
{
    if(lock!=NULL) {
        //锁定当前文件的写入锁
        lock->lockForWrite();
        int per = (f_ReceiveSize/f_FileSize)*100;
        //    qDebug() << "Download:" << f_File->fileName()<< ","  << buffer.size() <<"," << f_ReceiveSize << "," << f_FileSize;
        if(f_File!=NULL)
        {
            f_File->seek(pos);
            f_File->write(buffer);
        }

        lock->unlock();
    }
}
QString FileDownThread::getF_Url()
{
    //    qDebug() << f_Url;
    return !(f_Url.isEmpty())?f_Url:QString();
}

qint64 FileDownThread::GetFileSize(QUrl url)
{
    //用阻塞的方式获取下载文件的长度
    QNetworkAccessManager manager;
    //    qDebug() << "Getting the file size...";
    //开启一个事件循环
    QEventLoop loop;
    //发出请求，获取目标地址的头部信息
    QNetworkReply *reply = manager.head(QNetworkRequest(url));
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()), Qt::DirectConnection);
    loop.exec();
    if(reply->error() != QNetworkReply::NoError)
        return 0;
    QVariant var = reply->header(QNetworkRequest::ContentLengthHeader);
    delete reply;
    qint64 size = var.toLongLong();
    //    qDebug() << "The file size is: " << size;
    return size;
}
