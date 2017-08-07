#include "monitoringindicatorinfo.h"

MonitoringIndicatorInfo::MonitoringIndicatorInfo()
{
    IndicatorType = 0;
}

void MonitoringIndicatorInfo::toXML(QXmlStreamWriter *writer)
{
    this->BasicInfo::toXML(writer);
    writer->writeTextElement(trs("IndicatorType"),QString("%1").arg(IndicatorType));
}

void MonitoringIndicatorInfo::toEntity(QXmlStreamReader *reader)
{
    // 如果没有读到文档结尾，而且没有出现错误
    if(!reader->atEnd()) {
        // 读取下一个记号，它返回记号的类型
        QXmlStreamReader::TokenType type = reader->tokenType();
        QString name = reader->name().trimmed().toString();
        if(type == QXmlStreamReader::StartElement && !name.isEmpty()) {
            if(!name.isEmpty())
            {
                if(name=="IndicatorType")
                {
                    reader->readNext();
                    QString text = reader->text().trimmed().toString();
                    IndicatorType = text.toUInt();
                }
                else
                {
                    this->BasicInfo::toEntity(reader);
                }
            }
        }
    }
}



