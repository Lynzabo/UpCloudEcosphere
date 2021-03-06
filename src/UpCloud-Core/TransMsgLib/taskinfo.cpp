#include "taskinfo.h"

TaskInfo::TaskInfo()
{
    TaskUUID = 0;
}

void TaskInfo::toXML(QXmlStreamWriter *writer)
{
    this->BasicInfo::toXML(writer);
    writer->writeTextElement(trs("TaskUUID"),QString("%1").arg(TaskUUID));
}

void TaskInfo::toEntity(QXmlStreamReader *reader)
{
    // 如果没有读到文档结尾，而且没有出现错误
    if(!reader->atEnd()) {
        // 读取下一个记号，它返回记号的类型
        QXmlStreamReader::TokenType type = reader->tokenType();
        QString name = reader->name().trimmed().toString();
        if(type == QXmlStreamReader::StartElement && !name.isEmpty()) {
            if(!name.isEmpty())
            {
                if(name=="TaskUUID")
                {
                    reader->readNext();
                    QString text = reader->text().trimmed().toString();
                    TaskUUID = text.toUInt();
                }
                else
                {
                    this->BasicInfo::toEntity(reader);
                }
            }
        }
    }
}

