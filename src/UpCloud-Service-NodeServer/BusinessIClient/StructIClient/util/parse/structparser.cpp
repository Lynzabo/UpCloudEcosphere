#include "structparser.h"


StructParser::StructParser(QObject *parent)
{

}

void StructParser::init(const QList<QString> &fileList, const bool fileOutAsync, const quint32 fileOutAsyncCount, const bool fileInAsync, const quint32 fileInAsyncCount)
{
    for(int i=0; i<fileList.size(); i++)
    {
        m_fManagers.insert(fileList.at(i), F_STATE_UNPARSE);
    }
    m_fileOutAsync = fileOutAsync;
    m_fileOutAsyncCount = fileOutAsyncCount;
    m_fileInAsync = fileInAsync;
    m_fileInAsyncCount = fileInAsyncCount;
}

void StructParser::parse()
{
    //如果文件列表为空
    if(m_fManagers.isEmpty())
    {
        this->on_parseBegin();
        this->on_parseProcess(0);
        this->on_parseEnd();
        return;
    }
    //如果解析的文件之间存在依赖，则设置对于本次解析任务的解析线程数量为1，即单线程解析
    if(m_fileOutAsync == false)
    {
        m_fileOutAsyncCount = 1;
    }
    //如果每个文件内部存在依赖，则设置对于解析每个文件的线程数量为1，即但线程解析
    if(m_fileInAsync == false)
    {
        m_fileInAsyncCount = 1;
    }
    //根据解析文件之间的依赖性，生成指定数量的解析线程
    for(int i=0; i<m_fileOutAsyncCount;i++)
    {
        Struct1FileParser* sManager = new Struct1FileParser();        
        connect(sManager, SIGNAL(evt_parseError(QString,QString)), this, SLOT(on_subParseError(QString,QString)), Qt::QueuedConnection);
        connect(sManager, SIGNAL(evt_parseEnd(QString)), this, SLOT(on_subParseEnd(QString)), Qt::QueuedConnection);
        m_sManagers.insert(sManager, T_STATE_IDLE);
    }

    this->getTask();

}
void StructParser::getTask()
{
    //执行解析任务，直到所有的文件都解析完成（不管是解析成功还是失败）
    if(m_fManagers.values().contains(F_STATE_UNPARSE))
    {
        //[1]查询每个解析线程的状态，如果有线程处于空闲状态，则给此线程分配任务
        QList<quint8> managerState = m_sManagers.values();
        for(int i=0; i<managerState.size(); i++)
        {
            if(managerState.at(i) == T_STATE_IDLE)
            {
                //[2]查询出未解析的文件名
                QString fileName;
                QList<quint8> fileState = m_fManagers.values();
                for(int j=0; j<fileState.size(); j++)
                {
                    //遍历文件状态为 未解析的文件
                    if(fileState.at(j) == F_STATE_UNPARSE)
                    {
                        //得到文件名
                        fileName = m_fManagers.keys().at(j);
                        //修改文件状态为 正在解析
                        m_fManagers[fileName] = F_STATE_PARSING;
                        //初始化此线程
                        m_sManagers.keys().at(i)->init(fileName, m_fileInAsync, m_fileInAsyncCount);
                        //修改此线程状态为忙碌
                        m_sManagers[m_sManagers.keys().at(i)] = T_STATE_BUSY;
                        //启动本线程解析
                        m_sManagers.keys().at(i)->start();
                        //此线程任务分配完成，继续下个解析线程的任务分配
                        break;
                    }
                }
                //如果还有为解析的文件， 则继续分配任务
                if(m_fManagers.values().contains(F_STATE_UNPARSE))
                {
                    continue;
                }
                else
                {
                    break;
                }
            }
        }
    }
}

void StructParser::on_parseBegin()
{
    emit evt_parseBegin();
}

void StructParser::on_parseEnd()
{
    emit evt_parseEnd();
}

void StructParser::on_parseProcess(quint32 parsedCount)
{
    emit evt_parseProcess(parsedCount);
}

void StructParser::on_parseOneFileEnd(Struct1FileParser *sParseManager, const QString &fileName)
{
    QMutex mutex;
    mutex.lock();
    //修改此文件状态为 解析完成
    m_fManagers[fileName] = F_STATE_PARSED;
    //修改此线程状态为空闲
    m_sManagers[sParseManager] = T_STATE_IDLE;
    mutex.unlock();
    //发射信号
    emit evt_parseOneFileEnd(fileName);    
    //查询是否还有未解析的文件
    if(m_fManagers.values().contains(F_STATE_UNPARSE))
    {
        //如果还有未解析的任务，则去获取新的任务
        this->getTask();
    }
    else
    {
        //如果没有未解析的文件，则检查是否所有的任务都完成(因为有的任务也许正处在正在解析状态)
        if(m_fManagers.values().count(F_STATE_PARSED) == m_fManagers.size())
        {
            //如果所有的任务都处于解析完成状态，则说明本次任务完成
            this->on_parseEnd();
        }
    }

}

void StructParser::on_parseError(Struct1FileParser *sParseManager, const QString &fileName, const QString &errMsg)
{
    QMutex mutex;
    mutex.lock();
    //修改此文件状态为 解析完成
    m_fManagers[fileName] = F_STATE_PARSED;
    //修改此线程状态为空闲
    m_sManagers[sParseManager] = T_STATE_IDLE;
    mutex.unlock();
    //发射信号
    emit evt_parseError(fileName, errMsg);
    //查询是否还有未解析的文件
    if(m_fManagers.values().contains(F_STATE_UNPARSE))
    {
        //如果还有未解析的任务，则去获取新的任务
        this->getTask();
    }
    else
    {
        //如果没有未解析的文件，则检查是否所有的任务都完成(因为有的任务也许正处在正在解析状态)
        if(m_fManagers.values().count(F_STATE_PARSED) == m_fManagers.size())
        {
            //如果所有的任务都处于解析完成状态，则说明本次任务完成
            this->on_parseEnd();
        }
    }
}


//private slots
void StructParser::on_subParseError(const QString& fileName, const QString &errMsg)
{
    Struct1FileParser* sParseManager = (Struct1FileParser *)this->sender();
    this->on_parseError(sParseManager, fileName, errMsg);
}

void StructParser::on_subParseEnd(const QString &fileName)
{
    Struct1FileParser* sParseManager = (Struct1FileParser *)this->sender();
    this->on_parseOneFileEnd(sParseManager, fileName);
}
