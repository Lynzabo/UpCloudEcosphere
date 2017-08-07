#include "commonfilesdownloadinfo.h"

CommonFilesDownloadInfo::CommonFilesDownloadInfo()
{
    ftpPush = new FtpPush;
    httpPush = new HttpPush;
    TaskExecType = 0;
    Strategy = 0;
}

CommonFilesDownloadInfo::~CommonFilesDownloadInfo()
{
    delete ftpPush;
    delete httpPush;
}

void CommonFilesDownloadInfo::toXML(QXmlStreamWriter *writer)
{
    this->TaskInfo::toXML(writer);
    writer->writeTextElement(trs("TaskExecType"),QString("%1").arg(TaskExecType));
    writer->writeTextElement(trs("Strategy"),QString("%1").arg(Strategy));
    if(ftpPush->FilesDownloadURLs.size() > 0)
    {
        writer->writeStartElement("FtpPush");
        ftpPush->toXML(writer);
        writer->writeEndElement();
    }
    if(httpPush->FilesDownloadURLs.size()>0)
    {
        writer->writeStartElement("HttpPush");
        httpPush->toXML(writer);
        writer->writeEndElement();
    }
}

void CommonFilesDownloadInfo::toEntity(QXmlStreamReader *reader)
{
    // 如果没有读到文档结尾，而且没有出现错误
    if(!reader->atEnd()) {
        // 读取下一个记号，它返回记号的类型
        QXmlStreamReader::TokenType type = reader->tokenType();
        QString name = reader->name().trimmed().toString();
        if(type == QXmlStreamReader::StartElement && !name.isEmpty()) {
            if(name=="TaskExecType")
            {
                reader->readNext();
                //如果不是文本,就提示报文拼错
                QString text = reader->text().trimmed().toString();
                TaskExecType = text.toShort();
            }
            else if(name=="Strategy")
            {
                reader->readNext();
                QString text = reader->text().trimmed().toString();
                Strategy = text.toShort();
            }
            else if(name=="FtpPush")
           {
                ftpPush->toEntity(reader);
            }
            else if(name=="HttpPush")
            {
                httpPush->toEntity(reader);
            }
            else
            {
                this->TaskInfo::toEntity(reader);
            }
        }
    }
}

