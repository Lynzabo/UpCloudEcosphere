#include "reqscheduletaskdownloadinfo.h"

using namespace Environment::Datagram;

ReqScheduleTaskDownloadInfo::ReqScheduleTaskDownloadInfo()
{
    EntranceFile = "";
}

void ReqScheduleTaskDownloadInfo::toXML(QXmlStreamWriter *writer)
{
    TransException tsExcep;
    //校验实体是否合法,合法才可拼报文
    validate(tsExcep);
    //拼接报文
    writer->setAutoFormatting(true);
    writer->writeStartDocument();
    writer->writeStartElement("ReqScheduleTaskDownloadInfo");
    this->CommonFilesExecInfo::toXML(writer);
    writer->writeTextElement(trs("EntranceFile"),QString("%1").arg(EntranceFile));
    writer->writeEndElement();
    writer->writeEndDocument();
}

void ReqScheduleTaskDownloadInfo::toEntity(QXmlStreamReader *reader)
{
    TransException tsExcep;

    QXmlStreamReader::TokenType type = reader->readNext();
    type = reader->readNext();
    QString rootName = reader->name().trimmed().toString();
    if(rootName.isEmpty() || rootName != "ReqScheduleTaskDownloadInfo")
    {
        //不是中心分发预执行任务报文
        tsExcep.setType(Environment::Datagram::State::_3);
        tsExcep.setText(trs("未知报文类型"));
        throw tsExcep;
    }
    while(!reader->atEnd()) {
        type = reader->readNext();
        if (type == QXmlStreamReader::StartElement &&
                !reader->name().isEmpty()) {
            rootName = reader->name().trimmed().toString();
            if(rootName=="EntranceFile")
            {
                reader->readNext();
                QString text = reader->text().trimmed().toString();
                EntranceFile = text;
            }
            else
            {
                this->CommonFilesExecInfo::toEntity(reader);
            }
        }
    }
    // 解析XML报文出错
    if (reader->hasError()) {
        tsExcep.setType(Environment::Datagram::State::_1);
        tsExcep.setText(QString("%1,%2").arg(trs("中心分发预执行任务解析报文出错 ")).arg(reader->errorString()));
        throw tsExcep;
    }
    //校验报文是否合法,合法才可使用
    validate(tsExcep);
}

void ReqScheduleTaskDownloadInfo::validate(TransException &tsExcep)
{
    COMMON_VALIDATE(tsExcep,Sche_Data_Trans::REQSCHEDULETASKDOWNLOADINFO);
    //...
}

quint8 ReqScheduleTaskDownloadInfo::messageType() const
{
    return Sche_Data_Trans::REQSCHEDULETASKDOWNLOADINFO;
}




