#include "ftpcommonmanager.h"
#include <QDebug>
FtpCommonManager::FtpCommonManager()
{
    //初始化数据
    m_listInfo = NULL;
    m_objectName = "";
    //构建ftp对象
    m_qftp = new QFtp(this);
    //连接信号与槽
    QObject::connect(m_qftp, SIGNAL(commandStarted(int)),
                     this, SIGNAL(start()),Qt::DirectConnection);
    QObject::connect(m_qftp, SIGNAL(dataTransferProgress(qint64,qint64)),
                     this,SLOT(hander_process(qint64,qint64)),Qt::DirectConnection);
    QObject::connect(m_qftp, SIGNAL(commandFinished(int,bool)),
                     this, SLOT(hander_commandFinished(int, bool)),Qt::DirectConnection);
    QObject::connect(m_qftp, SIGNAL(listInfo(const QUrlInfo&)),
                     this, SLOT(hander_listInfo(const QUrlInfo&)),Qt::DirectConnection);
    //执行命令回执
    QObject::connect(m_qftp, SIGNAL(rawCommandReply(int,QString)),
                     this, SLOT(hander_rawCommandReply(int,QString)),Qt::DirectConnection);
}
FtpCommonManager::~FtpCommonManager()
{

}

void FtpCommonManager::init(FtpMeta *_meta)
{
    m_meta = _meta;
}

void FtpCommonManager::list(const QString &dir, QList<list_info> *listInfo)
{
    //连接服务器
    this->connect();
    //存储操作对象名（目录名/文件名）
    m_objectName = dir;
    //保存传出参数
    m_listInfo = listInfo;
    //执行命令
    m_qftp->list(dir);
    //退出
    m_qftp->close();
}

void FtpCommonManager::cd(const QString &dir)
{
    //连接服务器
    this->connect();
    //存储操作对象名（目录名/文件名）
    m_objectName = dir;
    //执行命令
    m_qftp->cd(dir);
    //退出
    m_qftp->close();
}

void FtpCommonManager::rename(const QString &oldname, const QString &newname)
{
    //连接服务器
    this->connect();
    //存储操作对象名（目录名/文件名）
    m_objectName = oldname;
    //执行命令
    m_qftp->rename(oldname, newname);
    //退出
    m_qftp->close();
}

void FtpCommonManager::remove(const QString &file)
{
    //连接服务器
    this->connect();
    //存储操作对象名（目录名/文件名）
    m_objectName = file;
    //执行命令
    m_qftp->remove(file);
    //退出
    m_qftp->close();
}

void FtpCommonManager::rmdir(const QString &dir)
{
    //连接服务器
    this->connect();
    //存储操作对象名（目录名/文件名）
    m_objectName = dir;
    // 执行命令
    m_qftp->rmdir(dir);
    //退出
    m_qftp->close();
}

void FtpCommonManager::mkdir(const QString &dir)
{
    //连接服务器
    this->connect();
    //存储操作对象名（目录名/文件名）
    m_objectName = dir;
    //执行命令
    m_qftp->mkdir(dir);
    //退出
    m_qftp->close();
}

void FtpCommonManager::size(const QString &fileUrl, qint64 *fileSize)
{
    //连接服务器
    this->connect();
    //存储文件大小
    m_fileSize = fileSize;
    //存储操作对象名（目录名/文件名）
    m_objectName = fileUrl;
    //执行命令
    m_qftp->rawCommand(QLatin1String("SIZE ") + fileUrl);
    //退出
    m_qftp->close();
}

//连接服务器
void FtpCommonManager::connect()
{
    //清空上次的结果
    this->clear();
    //连接ftp服务器
    m_qftp->connectToHost(m_meta->getHostname(),m_meta->getPort());
    m_qftp->login(m_meta->getUsername(),m_meta->getPassword());
}

void FtpCommonManager::clear()
{
    m_listInfo = NULL;
    m_objectName = "";
}
void FtpCommonManager::hander_listInfo(const QUrlInfo& urlInfo)
{
    struct list_info t_listInfo;
    if(urlInfo.isDir())
    {
        t_listInfo.isDir = true;
    }
    else
    {
        t_listInfo.isDir = false;
    }
    t_listInfo.name = urlInfo.name();
    t_listInfo.permissions = urlInfo.permissions();
    t_listInfo.owner = urlInfo.owner();
    t_listInfo.group = urlInfo.group();
    t_listInfo.size = urlInfo.size();
    t_listInfo.lastModified = urlInfo.lastModified();
    t_listInfo.lastRead = urlInfo.lastRead();
    (*m_listInfo).append(t_listInfo);
}

void FtpCommonManager::hander_process(qint64 haveDoneBytes, qint64 totalBytes)
{
    emit process(m_objectName, haveDoneBytes, totalBytes);
    qDebug() << "err_obj=" << m_objectName <<": haveDoneBytes=" <<haveDoneBytes << "totalBytes=" << totalBytes;
}

void FtpCommonManager::hander_rawCommandReply(int tmp, const QString &output)
{
    if(tmp == 213)
    {
        *m_fileSize = (qint64)output.toLongLong();
        qDebug() << "*m_fileSize=" << *m_fileSize;
    }
}

void FtpCommonManager::hander_commandFinished(int tmp, bool backSatus)
{
    Q_UNUSED(tmp);
    if(m_qftp->currentCommand() == QFtp::ConnectToHost)
    {
        if(backSatus)
        {
            emit
            error(m_objectName,QString("connect server error:%1").arg(m_qftp->errorString()));
            qDebug() << "err_obj=" << m_objectName <<": msg=" << m_qftp->errorString();
            return;
        }
        else
        {
            qDebug() << (tr("connect server success"));
        }
    }
    else if (m_qftp->currentCommand() == QFtp::Login)
    {
        if(backSatus)
        {
            emit
            error(m_objectName,QString("login error:%1").arg(m_qftp->errorString()));
            qDebug() << "err_obj=" << m_objectName <<": msg=" << m_qftp->errorString();
            return;
        }
        else
        {
            qDebug() << (tr("login success"));
        }
    }
    else if (m_qftp->currentCommand() == QFtp::List)
    {
        if(backSatus)
        {
            emit
            error(m_objectName,QString("list error:%1").arg(m_qftp->errorString()));
            qDebug() << "err_obj=" << m_objectName <<": msg=" << m_qftp->errorString();
            return;
        }
        else
        {
            qDebug() << "list success";
        }

    }
    else if (m_qftp->currentCommand() == QFtp::Cd)
    {
        if(backSatus)
        {
            emit
            error(m_objectName,QString("Cd error:%1").arg(m_qftp->errorString()));
            qDebug() << "err_obj=" << m_objectName <<": msg=" << m_qftp->errorString();
            return;
        }
        else
        {
            qDebug() << "Cd success";
        }

    }
    else if (m_qftp->currentCommand() == QFtp::Rename)
    {
        if(backSatus)
        {
            emit
            error(m_objectName,QString("Rename error:%1").arg(m_qftp->errorString()));
            qDebug() << "err_obj=" << m_objectName <<": msg=" << m_qftp->errorString();
            return;
        }
        else
        {
            qDebug() << "Rename success";
        }
    }
    else if (m_qftp->currentCommand() == QFtp::Remove)
    {
        if(backSatus)
        {
            emit
            error(m_objectName,QString("Remove error:%1").arg(m_qftp->errorString()));
            qDebug() << "err_obj=" << m_objectName <<": msg=" << m_qftp->errorString();
            return;
        }
        else
        {
            qDebug() << "Remove success";
        }
    }
    else if (m_qftp->currentCommand() == QFtp::Rmdir)
    {
        if(backSatus)
        {
            emit
            error(m_objectName,QString("Rmdir error:%1").arg(m_qftp->errorString()));
            qDebug() << "err_obj=" << m_objectName <<": msg=" << m_qftp->errorString();
            return;
        }
        else
        {
            qDebug() << "Rmdir success";
        }

    }
    else if (m_qftp->currentCommand() == QFtp::Mkdir)
    {
        if(backSatus)
        {
            emit
            error(m_objectName,QString("Mkdir error:%1").arg(m_qftp->errorString()));
            qDebug() << "err_obj=" << m_objectName <<": msg=" << m_qftp->errorString();
            return;
        }
        else
        {
            qDebug() << "Mkdir success";
        }
    }
    else if (m_qftp->currentCommand() == QFtp::Close)
    {
        if(backSatus)
        {
            emit
            error(m_objectName,QString("Close error:%1").arg(m_qftp->errorString()));
            qDebug() << "err_obj=" << m_objectName <<": msg=" << m_qftp->errorString();
            return;
        }
        else
        {
            qDebug() << "Close success";
        }
    }
}




