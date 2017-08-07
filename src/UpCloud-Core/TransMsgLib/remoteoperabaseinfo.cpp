#include "remoteoperabaseinfo.h"

RemoteOperaBaseInfo::RemoteOperaBaseInfo()
{    
    ExecType = 0;
    Params = "";
}


void RemoteOperaBaseInfo::toXML(QXmlStreamWriter *writer)
{
    this->BasicInfo::toXML(writer);
    writer->writeTextElement(trs("ExecType"),QString("%1").arg(ExecType));
    writer->writeTextElement(trs("Params"),QString("%1").arg(Params));
}

void RemoteOperaBaseInfo::toEntity(QXmlStreamReader *reader)
{
    // 如果没有读到文档结尾，而且没有出现错误
    if(!reader->atEnd()) {
        // 读取下一个记号，它返回记号的类型
        QXmlStreamReader::TokenType type = reader->tokenType();
        QString name = reader->name().trimmed().toString();
        if(type == QXmlStreamReader::StartElement && !name.isEmpty()) {
            if(!name.isEmpty())
            {
                if(name=="ExecType")
                {
                    reader->readNext();
                    QString text = reader->text().trimmed().toString();
                    ExecType = text.toUShort();
                }
                else if(name=="Params")
                {
                    reader->readNext();
                    QString text = reader->text().trimmed().toString();
                    Params = text;
                }
                else
                {
                    this->BasicInfo::toEntity(reader);
                }
            }
        }
    }
}




