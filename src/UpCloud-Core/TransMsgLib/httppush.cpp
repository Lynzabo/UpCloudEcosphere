#include "httppush.h"

HttpPush::HttpPush()
{
    this->FilesDownloadURLs.clear();
}

HttpPush::~HttpPush()
{
    qDeleteAll(FilesDownloadURLs);
    this->FilesDownloadURLs.clear();
}

void HttpPush::toXML(QXmlStreamWriter *writer)
{
    writer->writeStartElement("FilesDownloadURLs");
    for(int i = 0; i < this->FilesDownloadURLs.count(); i++)
    {
        FileDownload *fd = FilesDownloadURLs.at(i);
        writer->writeStartElement("FileDownload");
        fd->toXML(writer);
        delete fd;
        fd = NULL;
        writer->writeEndElement();
    }
    writer->writeEndElement();
}

void HttpPush::toEntity(QXmlStreamReader *reader)
{
    QString rootName = reader->name().trimmed().toString();
    // 输出http的所有节点
    while(!reader->atEnd()) {
        // 读取下一个记号，它返回记号的类型
        QXmlStreamReader::TokenType type = reader->tokenType();
        QString name = reader->name().trimmed().toString();
        if(type == QXmlStreamReader::StartElement && !name.isEmpty()) {
            if(name=="FilesDownloadURLs")
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

