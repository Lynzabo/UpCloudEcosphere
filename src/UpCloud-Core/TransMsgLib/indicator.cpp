#include "indicator.h"

Indicator::Indicator()
{
    IndicatorKey = 0;
    IndicatorValue = "";
}

Indicator::~Indicator()
{

}


void Indicator::toXML(QXmlStreamWriter *writer)
{
    writer->writeTextElement(trs("IndicatorKey"),QString("%1").arg(IndicatorKey));
    writer->writeTextElement(trs("IndicatorValue"),QString("%1").arg(IndicatorValue));
}
void Indicator::toEntity(QXmlStreamReader *reader)
{
    QString rootName = reader->name().trimmed().toString();
    // 如果没有读到文档结尾，而且没有出现错误
    while(!reader->atEnd()) {
        // 读取下一个记号，它返回记号的类型
        QXmlStreamReader::TokenType type = reader->tokenType();
        if(type == QXmlStreamReader::StartElement && !reader->name().isEmpty()) {
            QString name = reader->name().trimmed().toString();
            if(!name.isEmpty())
            {
                if(name=="IndicatorKey")
                {
                    reader->readNext();
                    QString text = reader->text().trimmed().toString();
                    IndicatorKey = text.toUShort();
                }
                else if(name=="IndicatorValue")
                {
                    reader->readNext();
                    QString text = reader->text().trimmed().toString();
                    IndicatorValue = text;
                }
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


