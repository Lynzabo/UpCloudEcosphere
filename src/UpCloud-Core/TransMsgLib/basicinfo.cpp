#include "basicinfo.h"
BasicInfo::BasicInfo()
{
    MessageType = 0;
    UUID = 0;
    RequestID = "";
}



void BasicInfo::toXML(QXmlStreamWriter *writer)
{
    writer->writeTextElement(trs("MessageType"),QString("%1").arg(MessageType));
    writer->writeTextElement(trs("UUID"),QString("%1").arg(UUID));
    writer->writeTextElement(trs("RequestID"),RequestID);
}

void BasicInfo::toEntity(QXmlStreamReader *reader)
{
    // 如果没有读到文档结尾，而且没有出现错误
    if(!reader->atEnd()) {
        // 读取下一个记号，它返回记号的类型
        QXmlStreamReader::TokenType type = reader->tokenType();
        if(type == QXmlStreamReader::StartElement && !reader->name().isEmpty()) {
            QString name = reader->name().trimmed().toString();
            if(!name.isEmpty())
            {
                if(name=="MessageType")
                {
                    type = reader->readNext();
                    QString text = reader->text().trimmed().toString();
                    MessageType = text.toShort();
                }
                else if(name=="UUID")
                {
                    type = reader->readNext();
                    QString text = reader->text().trimmed().toString();
                    UUID = text.toLongLong();
                }
                else if(name=="RequestID")
                {
                    type = reader->readNext();
                    QString text = reader->text().trimmed().toString();
                    RequestID = text;
                }
            }
        }
    }
}
