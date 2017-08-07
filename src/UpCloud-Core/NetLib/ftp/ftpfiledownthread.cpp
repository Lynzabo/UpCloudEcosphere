#include "ftpfiledownthread.h"
FtpFileDownThread::FtpFileDownThread(const QString &index)
{
    f_Key = index;
    f_File = new QFile;
    f_ReceiveSize = 0;
}

FtpFileDownThread::~FtpFileDownThread()
{
    if(f_File != NULL)
    {
        delete f_File;
        f_File = NULL;
    }
    if(qftp != NULL)
    {
        delete qftp;
        qftp = NULL;
    }
}

void FtpFileDownThread::SetDownloadProp(const QString &url, const QString &abstPath, const int &subAyncsSize, FtpMeta *_meta)
{
    meta = _meta;
    f_Url = url;
    f_SubAyncsSize = subAyncsSize;
    f_AbstPath = abstPath;
}

void FtpFileDownThread::run()
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

    //构建ftp对象
    qftp = new QFtp();
    //进度条显示
    connect(qftp,SIGNAL(dataTransferProgress(qint64,qint64)),
            this,SLOT(dataTransferProgress(qint64,qint64)),Qt::DirectConnection);
    //状态显示
    connect(qftp,SIGNAL(commandFinished(int,bool)),
            this,SLOT(dcommandFinish(int,bool)),Qt::DirectConnection);
    //执行命令回执
    connect(qftp, SIGNAL(rawCommandReply(int,QString)),
            this, SLOT(hander_size(int,QString)),Qt::DirectConnection);

    connect(qftp,SIGNAL(stateChanged(int)),
            this, SLOT(dcommandStateChanged(int)),Qt::DirectConnection);

    //quit exec
    connect(this,SIGNAL(endLoop()),
            this,SLOT(quit()),Qt::DirectConnection);


#if 0
    ////判断文件是否存在，如果存在就读取本地文件的大小和中心服务器上此文件的大小做比较，
    /// 如果大小一致，就不下载此文件，否则再继续下载此文件
    if(fileInfo.exists())
    {
        qint64 localSize = fileInfo.size();

        //获取远程服务器文件大小
        QString fileUrl = QUrl(f_Url).fileName();
        QEventLoop loop;

        //qftp->login(meta->getUsername(),meta->getPassword());
        qftp->rawCommand(QLatin1String("size ") + fileUrl);
        connect(this, SIGNAL(endLoop()), &loop, SLOT(quit()));
        loop.exec();

        if((quint64)localSize >= f_FileSize)
        {
            //进度条显示
            emit
            process(f_Url,f_FileSize,f_FileSize);
            //状态显示
            emit
            FileDownloadFinish(f_Key);
            return;
        }
    }
#endif

    QString fileName = f_AbstPath;
    f_File->setFileName(fileName);
    //打开文件
    if(f_File->open(QIODevice::WriteOnly | QIODevice::Truncate) == true)
    {
        qftp->connectToHost(meta->getHostname(),meta->getPort());
        qDebug()<<"ftp threadid:"<<QThread::currentThreadId()<<" connectToHost";
        this->exec();
    }
    else
    {
        emit
        FileDownloadError(f_Key,QString("Open file %1 fail").arg(f_AbstPath));
        qftp->close();
    }
}

void FtpFileDownThread::downloadFile()
{
    //qftp->rawCommand(tr("REST %1").arg(f_File->size()));
    //设置当前现在为续传
    //qftp->m_isConLoad = true;
    qftp->get(QUrl(f_Url).fileName(),f_File);
}

void FtpFileDownThread::dcommandFinish(int tmp, bool backSatus)
{
    qDebug() << this << "FtpFileDownThread::dcommandFinish begin" << qftp->currentCommand();
    Q_UNUSED(tmp);

    if(qftp->currentCommand() == QFtp::ConnectToHost)
    {
        if(backSatus)
        {
            f_File->close();
            emit FileDownloadError(f_Key,QString("connect server error:%1").arg(qftp->errorString()));
            qftp->close();
        }
        else
        {
            qDebug() << (tr("connect server success"));
            //登陆服务器
            qftp->login(meta->getUsername(),meta->getPassword());
        }
    }
    else if (qftp->currentCommand() == QFtp::Login)
    {
        if(backSatus)
        {
            f_File->close();
            emit FileDownloadError(f_Key,QString("login error:%1").arg(qftp->errorString()));
            qftp->close();
        }
        else
        {
            qDebug() << (tr("login success"));
            downloadFile();
        }
    }
    else if (qftp->currentCommand() == QFtp::Get)
    {
        if(backSatus)
        {
            f_File->close();
            emit FileDownloadError(f_Key,QString("download error:%1").arg(qftp->errorString()));
            qftp->close();
        }
        else
        {
            qDebug() << (tr("download success"));
            qftp->close();
            f_File->flush();
            f_File->close();
            emit FileDownloadFinish(f_Key);
        }
    }
    else if (qftp->currentCommand() == QFtp::Close)
    {
        qDebug() << (tr("close conn"));
        emit endLoop();
        return;
    }
    else
    {
        qDebug() << "Unknow command" << qftp->currentCommand();
        emit endLoop();
        return;
    }
}

void FtpFileDownThread::dcommandStateChanged(int state)
{
    if(state == 0)
    {
        emit endLoop();
        return;
    }
}

void FtpFileDownThread::dataTransferProgress(qint64 haveDoneBytes, qint64 totalBytes)
{
    emit
    process(f_Url,haveDoneBytes,totalBytes);
}

void FtpFileDownThread::hander_size(int tmp, const QString &output)
{
    if(tmp == 213)
    {
        f_FileSize = (qint64)output.toLongLong();
        qDebug() << "f_FileSize=" << f_FileSize;
    }
    emit
    endLoop();
}

QString FtpFileDownThread::getF_Url()
{
    return !(f_Url.isEmpty())?f_Url:QString();
}

