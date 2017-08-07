#include "commonfilesexecinfo.h"

CommonFilesExecInfo::CommonFilesExecInfo()
{

}

CommonFilesExecInfo::~CommonFilesExecInfo()
{

}

void CommonFilesExecInfo::toXML(QXmlStreamWriter *writer)
{
    this->CommonFilesDownloadInfo::toXML(writer);
    writer->writeTextElement(trs("ExecTime"),QString("%1").arg(ExecTime));
}

void CommonFilesExecInfo::toEntity(QXmlStreamReader *reader)
{
    // 如果没有读到文档结尾，而且没有出现错误
    if(!reader->atEnd()) {
        // 读取下一个记号，它返回记号的类型
        QXmlStreamReader::TokenType type = reader->tokenType();
        QString name = reader->name().trimmed().toString();
        if(type == QXmlStreamReader::StartElement && !name.isEmpty()) {
            if(!name.isEmpty())
            {
                if(name=="ExecTime")
                {
                    reader->readNext();
                    QString text = reader->text().trimmed().toString();
                    ExecTime = text;
                }
                else
                {
                    this->CommonFilesDownloadInfo::toEntity(reader);
                }
            }
        }
    }
}

