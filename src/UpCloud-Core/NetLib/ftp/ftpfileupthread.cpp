#include "ftpfileupthread.h"

FtpFileUpThread::FtpFileUpThread(const QString &index)
{
    f_Key = index;
    f_File = new QFile;
    f_ReceiveSize = 0;
}

FtpFileUpThread::~FtpFileUpThread()
{
    if(f_File != NULL)
    {
        delete f_File;
        f_File = NULL;
    }
    if(qftp != NULL)
    {
        this->qftp->deleteLater();
        qftp = NULL;
    }
}

void FtpFileUpThread::SetUploadProp(const QString &abstPath, const QString &url, const int &subAyncsSize, FtpMeta *_meta)
{
    meta = _meta;
    f_Url = url;
    f_SubAyncsSize = subAyncsSize;
    f_AbstPath = abstPath;
}

void FtpFileUpThread::run()
{
    //普通单个文件上传
    QString fileName = f_AbstPath;
    f_File->setFileName(fileName);
    //打开文件
    if(f_File->open(QIODevice::ReadOnly))
    {
        qDebug() << "open true";
    }
    else
    {
        qDebug() << "OPEN FALSE";
        emit
        FileUploadError(f_Key,QString("Open File %1 is error").arg(f_AbstPath));
        return;
    }
    //连接FTP
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

    //连接ftp服务器
    qftp->connectToHost(meta->getHostname(),meta->getPort());
    this->exec();
    if(qftp != NULL)
    {
        delete qftp;
        qftp = NULL;
    }
}

void FtpFileUpThread::uploadFile()
{
    //qftp->rawCommand(tr("REST %1").arg(f_File->size()));
    //设置当前现在为续传
    //qftp->m_isConLoad = true;
    qftp->put(f_File, f_Url);

}

void FtpFileUpThread::dcommandFinish(int tmp, bool backSatus)
{
    Q_UNUSED(tmp);
    if(qftp->currentCommand() == QFtp::ConnectToHost)
    {
        if(backSatus)
        {
            f_File->close();
            emit FileUploadError(f_Key,QString("connect server error:%1").arg(qftp->errorString()));
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
            emit FileUploadError(f_Key,QString("login error:%1").arg(qftp->errorString()));
            qftp->close();
        }
        else
        {
            qDebug() << (tr("login success"));
            uploadFile();
        }
    }
    else if (qftp->currentCommand() == QFtp::Put)
    {
        if(backSatus)
        {
            f_File->close();
            emit FileUploadError(f_Key,QString("upload error:%1").arg(qftp->errorString()));
            qftp->close();
        }
        else
        {
            qDebug() << (tr("upload success"));
            qftp->close();
            f_File->flush();
            f_File->close();
            emit FileUploadFinish(f_Key);
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

void FtpFileUpThread::dcommandStateChanged(int state)
{
    if(state == 0)
    {
        emit endLoop();
        return;
    }
}

void FtpFileUpThread::dataTransferProgress(qint64 haveDoneBytes, qint64 totalBytes)
{
    emit
    process(f_Url,haveDoneBytes,totalBytes);
}

void FtpFileUpThread::hander_size(int tmp, const QString &output)
{
    if(tmp == 213)
    {
        f_FileSize = (qint64)output.toLongLong();
        qDebug() << "f_FileSize=" << f_FileSize;
    }
    emit
    endLoop();
}

QString FtpFileUpThread::getF_AbstPath()
{
    return !(f_AbstPath.isEmpty())?f_AbstPath:QString();
}


