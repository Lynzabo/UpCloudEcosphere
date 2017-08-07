#include "struct1fileparser.h"

Struct1FileParser::Struct1FileParser()
{
    m_errors.clear();
    m_parsedCount = 0;

    m_parseBuilder = new StructParseMeta::Builder;
    m_structParseMeta = NULL;

    m_dbBuilder = new DatabaseMeta::Builder;
    m_dbMeta = NULL;
}

Struct1FileParser::~Struct1FileParser()
{
    m_errors.clear();

    if(m_parseBuilder != NULL)
    {
        delete m_parseBuilder;
    }
    m_parseBuilder = NULL;
    m_structParseMeta = NULL;

    if(m_dbBuilder != NULL)
    {
        delete m_dbBuilder;
    }
    m_dbBuilder = NULL;
    if(m_dbTransaction != NULL)
    {
        delete m_dbTransaction;
        m_dbTransaction = NULL;
    }

    m_parseDataThreads.clear();
}

void Struct1FileParser::init(const QString &fileName, bool async, quint32 asyncNum)
{
    m_fileName = fileName;
    m_async = async;
    m_asyncNum = asyncNum;
}


void Struct1FileParser::run()
{
    //开始解析
    emit evt_parseBegin();

    if(this->parseMeta() == false)
    {
        return;
    }
    this->getDbMeta();
    this->dbConnect();
    this->parseData();
}

void Struct1FileParser::on_parseError(const QString &errMsg)
{
    m_dbTransaction->rollback();
    //发送解析错误信号
    emit evt_parseError(m_fileName, errMsg);
}
bool Struct1FileParser::dbConnect()
{
    try{
        m_dbTransaction = new DBTransaction;
        m_dbTransaction->setDatabaseMeta(*m_dbMeta);
        m_dbTransaction->beginTransaction();
    }
    catch(DBException &ex)
    {
        QString errMsg = QString("DbConn:%1,%2,%3").arg(ex.getType()).arg(ex.getTypeDesc()).arg(ex.getText());
        emit evt_parseError(m_fileName,errMsg);
        return false;
    }
    return true;
}

void Struct1FileParser::on_subPareDataEnd()
{
    //修改当前线程对应的状态为true代表该解析线程结束
    StructParseDataThread* parseDataThreads = (StructParseDataThread*)this->sender();
    m_parseDataThreads[parseDataThreads] = true;

    //如果所有的解析线程都解析结束 则表示此任务解析完成
    QList<bool> threadStates = m_parseDataThreads.values();
    //all task is complete
    if(!threadStates.contains(false))
    {
        m_dbTransaction->commit();
        //发送解析完成信号
        emit evt_parseEnd(m_fileName);
    }
}

void Struct1FileParser::on_subPareDataItem()
{
    m_parsedCount ++;
    // quint8 ans = (quint8)(QString::number(((double)(m_parsedCount*100))/m_size, 'f', 2).toDouble());
    qDebug() <<"@m_parsedCount=" << m_parsedCount;
    emit evt_parseProcess(m_parsedCount);
}

bool Struct1FileParser::parseMeta()
{
    QFile file(m_fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        //打开文件失败
        emit evt_parseError(m_fileName, "Error: Cannot read file!");
        return false;
    }
    QXmlStreamReader reader;
    reader.setDevice(&file);

    //解析XML，直到结束
    while(!reader.atEnd() && !reader.hasError())
    {
        //读取下一个element.
        QXmlStreamReader::TokenType token = reader.readNext();
        //如果获取的仅为StartDocument,则进行下一个
        if(token == QXmlStreamReader::StartDocument)
        {
            continue;
        }
        //如果获取了StartElement,则尝试读取
        if(token == QXmlStreamReader::StartElement)
        {
            //如果为UpCloud，直接进入下一个
            if(reader.name() == "UpCloud")
            {
                continue;
            }
            //如果为Database，则对其进行解析
            if(reader.name() == "Database")
            {
                //操作下一个
                reader.readNext();
                while(!(reader.tokenType() == QXmlStreamReader::EndElement &&
                        reader.name() == "Database"))
                {
                    if(reader.tokenType() == QXmlStreamReader::StartElement)
                    {
                        if(reader.name() == "DbType")
                        {
                            reader.readNext();
                            QString text = reader.text().trimmed().toString();
                            //                            StructParseMeta::DbType dbType;
                            //                            if(QString::compare(text, "Oracle", Qt::CaseInsensitive) == 0)
                            //                            {
                            //                                dbType = StructParseMeta::DbType::Oracle;
                            //                            }
                            //                            else if(QString::compare(text, "MySQL", Qt::CaseInsensitive) == 0)
                            //                            {
                            //                                dbType = StructParseMeta::DbType::MySQL;
                            //                            }
                            //                            else if(QString::compare(text, "SQLite3", Qt::CaseInsensitive) == 0)
                            //                            {
                            //                                dbType = StructParseMeta::DbType::SQLite3;
                            //                            }
                            m_parseBuilder->setDatabase(text);
                            qDebug() << "DbType=" << text;
                        }
                        if(reader.name() == "IP")
                        {
                            reader.readNext();
                            QString text = reader.text().trimmed().toString();
                            m_parseBuilder->setIp(text);
                            qDebug() << "IP=" << text;
                        }
                        if(reader.name() == "Port")
                        {
                            reader.readNext();
                            QString text = reader.text().trimmed().toString();
                            m_parseBuilder->setPort(text.toUShort());
                            qDebug() << "Port=" << text.toUShort();
                        }
                        if(reader.name() == "InstanceName")
                        {
                            reader.readNext();
                            QString text = reader.text().trimmed().toString();
                            m_parseBuilder->setDatabaseName(text);
                            qDebug() << "DatabaseName=" << text;
                        }
                        if(reader.name()=="Username")
                        {
                            reader.readNext();
                            QString text = reader.text().trimmed().toString();
                            m_parseBuilder->setUsername(text);
                            qDebug() << "Username=" << text;
                        }
                        if(reader.name()=="Password")
                        {
                            reader.readNext();
                            QString text = reader.text().trimmed().toString();
                            m_parseBuilder->setPassword(text);
                            qDebug() << "Password=" << text;
                        }
                        if(reader.name()=="HouseKeepingSleepTime")
                        {
                            reader.readNext();
                            int text = reader.text().toInt();
                            m_parseBuilder->setHouseKeepingSleepTime(text);
                            qDebug() << "HouseKeepingSleepTime=" << text;
                        }
                        if(reader.name()=="WaitIntervalTime")
                        {
                            reader.readNext();
                            int text = reader.text().toInt();
                            m_parseBuilder->setWaitIntervalTime(text);
                            qDebug() << "WaitIntervalTime=" << text;
                        }
                    }
                    reader.readNext();
                }

                m_structParseMeta = m_parseBuilder->setAsync(m_async)->setAsyncNum(m_asyncNum)->build();
            }
            //如果为Datas，则对其进行解析
            if(reader.name() == "Datas")
            {
                //获取Datas属性
                QXmlStreamAttributes attributes = reader.attributes();
                if(attributes.hasAttribute("Size"))
                {
                    m_size = attributes.value("Size").toUInt();
                    qDebug() << "Size=" << attributes.value("Size").toString();
                    break;
                }
            }
        }
    }

    if(reader.hasError())
    {
        //解析出错
        emit  evt_parseError(m_fileName, reader.errorString());
        //从reader中删除所有设备、数据，并将其重置为初始状态
        reader.clear();
        qDebug() <<"SubThread_End:"<<this;
        return false;
    }
    //解析完成
    //从reader中删除所有设备、数据，并将其重置为初始状态
    reader.clear();
    qDebug() <<"SubThread_End:"<<this;
    return true;
}

//生成数据库元数据
void Struct1FileParser::getDbMeta()
{
    DatabaseMeta::Builder *m_dbBuilder = new DatabaseMeta::Builder;
    m_dbMeta = m_dbBuilder->setDbName(m_structParseMeta->getDatabase())//设置数据库类型
            ->setIp(m_structParseMeta->getIp())//数据库IP
            ->setPort(m_structParseMeta->getPort())//数据库端口
            ->setInstanceName(m_structParseMeta->getDatabaseName())//数据库名称
            ->setUsername(m_structParseMeta->getUsername())//数据库用户名
            ->setPassword(m_structParseMeta->getPassword())//数据库密码
            ->setHouseKeepingSleepTime(m_structParseMeta->getHouseKeepingSleepTime()) //连接超时时间(ms为单位)
            ->setWaitIntervalTime(m_structParseMeta->getWaitIntervalTime()) //等待间隔时间(ms为单位)
            ->build();
}

void Struct1FileParser::parseData()
{
    //如果要解析的条目数为0，则不用解析直接返回
    if(m_size<=0)
    {
        return;
    }
    //TODO 如果给的支持多路解析,通道数量却为0，就认识是填错了，给他分配一个线程去解析
    if(m_asyncNum == 0)
    {
        m_asyncNum = 1;
    }

    //分组排序
    this->group();

    //创建解析数据线程组
    for(int i=0; i<m_asyncNum; i++)
    {
        StructParseDataThread* parseDataThread = new StructParseDataThread
                (m_fileName, m_begEnds.keys().at(i), m_begEnds.values().at(i), m_dbTransaction);
        quint32 begin = m_begEnds.keys().at(i);
        quint32 end = m_begEnds.values().at(i);
        qDebug() << "i=" << i << " " << "begin=" << begin <<" "<<"end=" <<end;
        //连接子解析的解析错误信号，数据库错误信号和执行一条操作结束信号，全部解析结束信号
        //one block one item parse end
        connect(parseDataThread, SIGNAL(evt_subPareDataItem()), this, SLOT(on_subPareDataItem()), Qt::QueuedConnection);
        //one block parse end
        connect(parseDataThread, SIGNAL(evt_subPareDataEnd()), this, SLOT(on_subPareDataEnd()), Qt::QueuedConnection);

        connect(parseDataThread, SIGNAL(evt_parseError(QString)), this, SLOT(on_parseError(QString)), Qt::QueuedConnection);
        m_parseDataThreads.insert(parseDataThread,false);
    }
    //启动解析数据线程组
    for(int i=0; i<m_parseDataThreads.size(); i++)
    {
        m_parseDataThreads.keys().at(i)->start();
    }
}



void Struct1FileParser::group()
{
    if(m_async == false)
    {
        m_asyncNum = 1;
    }

    if(m_async == false)
    {
        m_begEnds.insert((quint32)1, m_size);
    }
    else
    {
        //如果要解析的数据条目数大于同步下载的个数
        if(m_size>=m_asyncNum)
        {
            quint32 average = m_size/m_asyncNum;
            quint32 remainder = m_size%m_asyncNum;
            static quint32 pre = 0;
            for(quint32 i=0; i<m_asyncNum; i++)
            {
                //整除的情况
                if(remainder == 0)
                {
                    m_begEnds.insert(pre+1, pre+average);
                    pre = pre+average;
                }
                //有余数的情况
                else
                {
                    if(remainder == 0)
                    {
                        m_begEnds.insert(pre+1, pre+average);
                    }
                    else
                    {
                        //如果不是完全平均分配，就对从第一个下载线程开始每个加1条数据解析的任务直到分配完成即余数为0
                        m_begEnds.insert(pre+1, pre+1+average);
                        pre = pre+1+average;
                        remainder--;
                    }
                }
            }
            pre = 0;
        }
        //TODO 如果要解析的数据条目数小于同步下载的个数
        else
        {
            m_begEnds.insert((quint32)1, m_size);
            m_asyncNum = 1;
        }
    }
}
