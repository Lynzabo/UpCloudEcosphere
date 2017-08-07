#include "resultinfo.h"

ResultInfo::ResultInfo()
{
    this->results.clear();
}

ResultInfo::~ResultInfo()
{
    for(int i = 0; i < this->results.count(); i++)
    {
        delete this->results.at(i);
    }
    this->results.clear();
}

void ResultInfo::toXML(QXmlStreamWriter *writer)
{
    writer->writeStartElement("results");
    for(int i = 0; i < this->results.count(); i++)
    {
        Result *er = results.at(i);
        writer->writeStartElement("Result");
        er->toXML(writer);
       //TODO
	   // delete er;
        //er = NULL;
        writer->writeEndElement();
    }
    writer->writeEndElement();
}

void ResultInfo::toEntity(QXmlStreamReader *reader)
{
    QString rootName = reader->name().trimmed().toString();
    // 输出ftp的所有节点
    while(!reader->atEnd()) {
        // 读取下一个记号，它返回记号的类型
        QXmlStreamReader::TokenType type = reader->tokenType();
        QString name = reader->name().trimmed().toString();
        if(type == QXmlStreamReader::StartElement && !name.isEmpty()) {
            if(name=="results")
            {
                while(!reader->atEnd())
                {
                    type = reader->readNext();
                    QString nodeName = reader->name().trimmed().toString();
                    if(type == QXmlStreamReader::StartElement && !nodeName.isEmpty()) {
                        Result *er = new Result;
                        er->toEntity(reader);
                        results.append(er);
                    }
                    if(type == QXmlStreamReader::EndElement && !nodeName.isEmpty()) {
                        if(name == nodeName)
                        {
                            goto label;
                        }
                    }
                }
                label:;
            }
        }
        QString nodeName2 = reader->name().trimmed().toString();
        if(type == QXmlStreamReader::EndElement && !nodeName2.isEmpty()) {
            if(rootName == nodeName2)
            {
                goto label2;
            }
        }
        reader->readNext();
    }
    label2:;
}



