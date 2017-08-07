#include "parsesdpoolimpl.h"


ParseSDPoolImpl::ParseSDPoolImpl()
{
    m_parseManager = NULL;
}

ParseSDPoolImpl::~ParseSDPoolImpl()
{
    if(m_parseManager != NULL)
    {
        delete m_parseManager;
        m_parseManager = NULL;
    }
}

void ParseSDPoolImpl::parse(const QList<QString> &fileList, const bool fileOutAsync, const quint32 fileOutAsyncCount, const bool fileInAsync, const quint32 fileInAsyncCount)
{
    m_parseManager = new StructParser;
    m_parseManager->init(fileList, fileOutAsync, fileOutAsyncCount, fileInAsync, fileInAsyncCount);
    connect(m_parseManager, SIGNAL(evt_parseBegin()), this, SLOT(on_parseBegin()), Qt::QueuedConnection);
    connect(m_parseManager, SIGNAL(evt_parseEnd()), this, SLOT(on_parseEnd()), Qt::QueuedConnection);
    connect(m_parseManager, SIGNAL(evt_parseProcess(quint32)), this, SLOT(on_parseProcess(quint32)), Qt::QueuedConnection);
    connect(m_parseManager, SIGNAL(evt_parseOneFileEnd(QString)), this, SLOT(on_parseOneFileEnd(QString)), Qt::QueuedConnection);
    connect(m_parseManager, SIGNAL(evt_parseError(QString,QString)), this, SLOT(on_parseError(QString,QString)), Qt::QueuedConnection);
    m_parseManager->parse();
}

void ParseSDPoolImpl::on_parseBegin()
{
    qDebug() << "begin";
    //传输开始
    emit
        evt_parseBegin();
}

void ParseSDPoolImpl::on_parseEnd()
{
    qDebug() << "end";
    //传输结束
    emit
    evt_parseEnd();
}

void ParseSDPoolImpl::on_parseProcess(quint32 parsedCount)
{
    qDebug() << "parseProcess";
    //文件解析进度
    emit
        evt_parseProcess(parsedCount);
}

void ParseSDPoolImpl::on_parseError(const QString &fileName, const QString &errMsg)
{
    qDebug() << "parseError";
    //某个文件解析错误
    emit
        evt_parseError(fileName, errMsg);
}

void ParseSDPoolImpl::on_parseOneFileEnd(const QString &fileName)
{
    qDebug() << "parseOneFileEnd";
    //某个文件解析完成
    emit
        evt_parseOneFileEnd(fileName);
}
