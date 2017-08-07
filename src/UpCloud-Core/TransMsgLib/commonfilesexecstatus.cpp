#include "commonfilesexecstatus.h"

CommonFilesExecStatus::CommonFilesExecStatus()
{
    State = 0;
    Strategy = 0;
    resultInfo = new ResultInfo;
}

CommonFilesExecStatus::~CommonFilesExecStatus()
{
    delete resultInfo;
}

void CommonFilesExecStatus::toXML(QXmlStreamWriter *writer)
{
    this->TaskInfo::toXML(writer);
    writer->writeTextElement(trs("State"),QString("%1").arg(State));
    writer->writeTextElement(trs("Strategy"),QString("%1").arg(Strategy));
    if(resultInfo->results.size() > 0)
    {
        writer->writeStartElement("resultInfo");
        resultInfo->toXML(writer);
        writer->writeEndElement();
    }
}

void CommonFilesExecStatus::toEntity(QXmlStreamReader *reader)
{
    // 如果没有读到文档结尾，而且没有出现错误
    if(!reader->atEnd()) {
        // 读取下一个记号，它返回记号的类型
        QXmlStreamReader::TokenType type = reader->tokenType();
        QString name = reader->name().trimmed().toString();
        if(type == QXmlStreamReader::StartElement && !name.isEmpty()) {
            if(name=="State")
            {
                reader->readNext();
                //如果不是文本,就提示报文拼错
                QString text = reader->text().trimmed().toString();
                State = text.toShort();
            }
            else if(name=="Strategy")
            {
                reader->readNext();
                QString text = reader->text().trimmed().toString();
                Strategy = text.toShort();
            }
            else if(name=="resultInfo")
            {
                resultInfo->toEntity(reader);
            }
            else
            {
                this->TaskInfo::toEntity(reader);
            }
        }
    }
}



