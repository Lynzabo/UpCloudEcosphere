#include "structparsedatathread.h"

void StructParseDataThread::run()
{
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
                                if(QString::compare(Type, "Insert") == 0)
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
                            }

                            //获取Data内容
                            reader.readNext();
                            QString text = reader.text().trimmed().toString();
                            m_currentData.setInfo(reader.text().trimmed().toString());
                            //qDebug() <<"ref=" << ref << " " << "Type=" << Type << " "<< "Date=" << text <<this;
                            if(this->parseDataItem() == false)
                            {
                                //如果执行某个数据操作失败就返回
                                goto PARSEEND;
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
        emit
        evt_parseError(reader.errorString());
        //从reader中删除所有设备、数据，并将其重置为初始状态
        reader.clear();
        qDebug() <<"SubThread_Error"<<this;
        return;
    }
PARSEEND:
    //解析Meta完成
    emit
    evt_subPareDataEnd();
    //从reader中删除所有设备、数据，并将其重置为初始状态
    reader.clear();
    qDebug() <<"SubThread_End:"<<this;
    return;
}

bool StructParseDataThread::parseDataItem()
{
    qDebug() <<"ref=" << m_currentData.getRef() << " " << "Type=" << m_currentData.getType()
            << " "<< "Date=" << m_currentData.getInfo() <<this;
#if 0
    //TODO 数据库任务
    //因为这里的key为整形,所以可以这样判断
    try{
        QVariantMap params;
        params.clear();
        bool stats = m_dbTransaction.execSQL(m_currentData.getInfo(), params);
        if(stats == true)
        {
            qDebug() << trs("execSQL OK!");
            emit evt_subPareDataItem(m_parsedCount);
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
        emit evt_dbExecError(m_currentData, ex);
        return false;
    }
#endif
    emit evt_subPareDataItem();
    return true;
}
