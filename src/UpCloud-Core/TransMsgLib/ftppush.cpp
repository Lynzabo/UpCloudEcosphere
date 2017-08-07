#include "ftppush.h"

FtpPush::FtpPush()
{
    this->FilesDownloadURLs.clear();
    IP = "";
    Port = 0;
    Username = "";
    Password = "";
}

FtpPush::~FtpPush()
{
    qDeleteAll(FilesDownloadURLs);
    this->FilesDownloadURLs.clear();
}

void FtpPush::toXML(QXmlStreamWriter *writer)
{
    writer->writeStartElement("FilesDownloadURLs");
    for(int i = 0; i < this->FilesDownloadURLs.count(); i++)
    {
        FileDownload *fd = FilesDownloadURLs.at(i);
        writer->writeStartElement("FileDownload");
        fd->toXML(writer);
		//TODO
        //delete fd;
        //fd = NULL;
        //TODO
        writer->writeEndElement();
    }
    writer->writeEndElement();
    writer->writeTextElement(trs("IP"),QString("%1").arg(IP));
    writer->writeTextElement(trs("Port"),QString("%1").arg(Port));
    writer->writeTextElement(trs("Username"),QString("%1").arg(Username));
    writer->writeTextElement(trs("Password"),QString("%1").arg(Password));
}

void FtpPush::toEntity(QXmlStreamReader *reader)
{
    QString rootName = reader->name().trimmed().toString();
    // 输出ftp的所有节点
    while(!reader->atEnd()) {
        // 读取下一个记号，它返回记号的类型
        QXmlStreamReader::TokenType type = reader->tokenType();
        QString name = reader->name().trimmed().toString();
        if(type == QXmlStreamReader::StartElement && !name.isEmpty()) {
            if(name=="IP")
            {
                reader->readNext();
                QString text = reader->text().trimmed().toString();
                IP = text;
            }
            else if(name=="Port")
            {
                reader->readNext();
                QString text = reader->text().trimmed().toString();
                Port = text.toShort();
            }
            else if(name=="Username")
            {
                reader->readNext();
                QString text = reader->text().trimmed().toString();
                Username = text;
            }
            else if(name=="Password")
            {
                reader->readNext();
                QString text = reader->text().trimmed().toString();
                Password = text;
            }
            else if(name=="FilesDownloadURLs")
            {
                while(!reader->atEnd())
                {
                    type = reader->readNext();
                    QString nodeName = reader->name().trimmed().toString();
                    if(type == QXmlStreamReader::StartElement && !nodeName.isEmpty()) {
                        FileDownload *fd = new FileDownload;
                        fd->toEntity(reader);
                        FilesDownloadURLs.append(fd);
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

