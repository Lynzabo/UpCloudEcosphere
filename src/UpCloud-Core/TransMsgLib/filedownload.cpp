#include "filedownload.h"

FileDownload::FileDownload()
{

}

void FileDownload::toXML(QXmlStreamWriter *writer)
{
    writer->writeTextElement(trs("DownloadURLs"),QString("%1").arg(DownloadURLs));
    writer->writeTextElement(trs("DescPath"),QString("%1").arg(DescPath));
}

void FileDownload::toEntity(QXmlStreamReader *reader)
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
                if(name=="DownloadURLs")
                {
                    reader->readNext();
                    QString text = reader->text().trimmed().toString();
                    DownloadURLs = text;
                }
                else if(name=="DescPath")
                {
                    reader->readNext();
                    QString text = reader->text().trimmed().toString();
                    DescPath = text;
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

