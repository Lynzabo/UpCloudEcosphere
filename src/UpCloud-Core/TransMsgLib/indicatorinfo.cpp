#include "indicatorinfo.h"

IndicatorInfo::IndicatorInfo()
{
    this->Indicators.clear();
}

IndicatorInfo::~IndicatorInfo()
{
    for(int i = 0; i < this->Indicators.count(); i++)
    {
        delete this->Indicators.at(i);
    }
    this->Indicators.clear();
}

void IndicatorInfo::toXML(QXmlStreamWriter *writer)
{
    writer->writeStartElement("Indicators");
    for(int i = 0; i < this->Indicators.count(); i++)
    {
        Indicator *indicat = Indicators.at(i);
        writer->writeStartElement("Indicator");
        indicat->toXML(writer);
        delete indicat;
        indicat = NULL;
        writer->writeEndElement();
    }
    writer->writeEndElement();
}

void IndicatorInfo::toEntity(QXmlStreamReader *reader)
{
    QString rootName = reader->name().trimmed().toString();
    // 输出Indicators的所有节点
    while(!reader->atEnd()) {
        // 读取下一个记号，它返回记号的类型
        QXmlStreamReader::TokenType type = reader->tokenType();
        QString name = reader->name().trimmed().toString();
        if(type == QXmlStreamReader::StartElement && !name.isEmpty()) {
            if(name=="Indicators")
            {
                while(!reader->atEnd())
                {
                    type = reader->readNext();
                    QString nodeName = reader->name().trimmed().toString();
                        if(type == QXmlStreamReader::StartElement && !nodeName.isEmpty()) {
                            Indicator *indicat = new Indicator;
                            indicat->toEntity(reader);
                            Indicators.append(indicat);
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





