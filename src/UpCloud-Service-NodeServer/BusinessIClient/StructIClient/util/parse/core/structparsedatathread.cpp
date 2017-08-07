#include "structparsedatathread.h"

StructParseDataThread::~StructParseDataThread()
{
}

void StructParseDataThread::run()
{

    //打开文件
    QFile file(m_xmlFilePath);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        emit evt_parseError("Error: Cannot read file!");
        return;
    }
    QXmlStreamReader reader;
    reader.setDevice(&file);

    //开始解析
    emit evt_subParseDataBegin();
    qDebug() <<"SubThread_Begin"<<this;
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
            //如果为Datas，则对其进行解析
            if(reader.name() == "Datas")
            {
                //操作下一个
                reader.readNext();
                while(!(reader.tokenType() == QXmlStreamReader::EndElement &&
                        reader.name() == "Datas"))
                {
                    if(reader.tokenType() == QXmlStreamReader::StartElement)
                    {
                        if((reader.name() == "Data"))
                        {
                            //获取Data属性
                            QXmlStreamAttributes attributes = reader.attributes();
                            QString ref = "";
                            QString Type = "";
                            if(attributes.hasAttribute("ref"))
                            {
                                ref = attributes.value("ref").toString();
                                m_currentData.setRef((quint32)ref.toUInt());
                            }
                            if(ref.toUInt() < m_refBegin)
                            {
                                reader.readNext();
                                continue;
                            }
                            else if(ref.toUInt() > m_refEnd)
                            {
                                goto PARSEEND;
                            }
                            if(attributes.hasAttribute("Type"))
                            {
                                Type = attributes.value("Type").toString();
                                StructParseData::Type dataType;
                                if(QString::compare(Type, "Create") == 0)
                                {
                                    dataType = StructParseData::Type::Create;
                                    m_currentData.setType(StructParseData::Type::Create);
                                }
                                else if(QString::compare(Type, "Select") == 0)
                                {
                                    dataType = StructParseData::Type::Select;
                                    m_currentData.setType(StructParseData::Type::Select);
                                }
                                else if(QString::compare(Type, "Insert") == 0)
                                {
                                    dataType = StructParseData::Type::Insert;
                                    m_currentData.setType(StructParseData::Type::Insert);
                                }
                                else if(QString::compare(Type, "Update") == 0)
                                {
                                    dataType = StructParseData::Type::Update;
                                    m_currentData.setType(StructParseData::Type::Update);
                                }
                                else if(QString::compare(Type, "Delete") == 0)
                                {
                                    dataType = StructParseData::Type::Delete;
                                    m_currentData.setType(StructParseData::Type::Delete);
                                }
                                else if(QString::compare(Type, "Drop") == 0)
                                {
                                    dataType = StructParseData::Type::Drop;
                                    m_currentData.setType(StructParseData::Type::Drop);
                                }
                            }

                            //获取Data内容
                            reader.readNext();
                            reader.readNext();
                            if(reader.name() == "sql")
                            {
                                reader.readNext();
                                m_currentData.setInfo(reader.text().trimmed().toString());
                            }
                            //获取参数列表
                            while(!(reader.tokenType() == QXmlStreamReader::EndElement &&
                                    reader.name() == "params"))
                            {
                                if((reader.tokenType() == QXmlStreamReader::StartElement && reader.name() == "param"))
                                {
                                    QXmlStreamAttributes attributes = reader.attributes();
                                    QString name = "";
                                    if(attributes.hasAttribute("name"))
                                    {
                                        name = attributes.value("name").toString();
                                    }
                                    reader.readNext();
                                    QString value = "";
                                    value = reader.text().trimmed().toString();
                                    m_currentData.setParamsArgs(name, value);
                                }
                                reader.readNext();
                            }
                            if(this->parseDataItem() == false)
                            {
                                //如果执行某个数据操作失败就返回
                                //从reader中删除所有设备、数据，并将其重置为初始状态
                                reader.clear();
                                qDebug() <<"SubThread_End:"<<this;
                                return;
                            }
                        }
                    }
                    reader.readNext();
                }
            }
        }
    }
    if(reader.hasError())
    {
        //解析出错
        emit evt_parseError(reader.errorString());
        //从reader中删除所有设备、数据，并将其重置为初始状态
        reader.clear();
        qDebug() <<"SubThread_End:"<<this;
        return;
    }
PARSEEND:
    //解析Meta完成
    emit evt_subPareDataEnd();
    //从reader中删除所有设备、数据，并将其重置为初始状态
    reader.clear();
    qDebug() <<"SubThread_End:"<<this;
    return;
}

bool StructParseDataThread::parseDataItem()
{
    //TODO 数据库任务
    try{
        bool stats = false;
        StructParseData::Type dataType = m_currentData.getType();
        if(dataType == StructParseData::Type::Insert)
        {
            stats = m_dbTransaction->insert(m_currentData.getInfo(), m_currentData.getParams());

        }
        else
        {
            stats = m_dbTransaction->execSQL(m_currentData.getInfo(), m_currentData.getParams());
        }
        if(stats == true)
        {
            qDebug() << trs("execSQL OK!");
            emit evt_subPareDataItem();
            return true;
        }
        else
        {
            qDebug() << trs("execSQL Fail!");
            DBException excep;
            excep.setType(QSqlError::TransactionError);
            excep.setText(trs("Exec Error"));
            throw excep;
        }
    }
    catch(DBException &ex)
    {
        qDebug() << trs("ExecDB Error!");
        //回滚事务
        m_dbTransaction->rollback();
        //发射解析错误信号
        QString dbError = trs("%1,%2,%3,sql:%4").arg(ex.getType()).arg(ex.getTypeDesc()).arg(ex.getText()).arg(m_currentData.getInfo());
        QString errMsg = QString("DbExec:[%1]:%2").arg(m_currentData.getInfo()).arg(dbError);

        emit evt_parseError(errMsg);
        return false;
    }
}

