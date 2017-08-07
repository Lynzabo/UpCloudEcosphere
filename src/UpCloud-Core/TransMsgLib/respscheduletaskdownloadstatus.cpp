#include "respscheduletaskdownloadstatus.h"

using namespace Environment::Datagram;

RespScheduleTaskDownloadStatus::RespScheduleTaskDownloadStatus()
{

}

RespScheduleTaskDownloadStatus::~RespScheduleTaskDownloadStatus()
{

}

void RespScheduleTaskDownloadStatus::toXML(QXmlStreamWriter *writer)
{
    TransException tsExcep;
    //校验实体是否合法,合法才可拼报文
    validate(tsExcep);
    //拼接报文
    writer->setAutoFormatting(true);
    writer->writeStartDocument();
    writer->writeStartElement("RespScheduleTaskDownloadStatus");
    this->TaskReplyInfo::toXML(writer);
    writer->writeEndElement();
    writer->writeEndDocument();
}

void RespScheduleTaskDownloadStatus::toEntity(QXmlStreamReader *reader)
{
    TransException tsExcep;

    QXmlStreamReader::TokenType type = reader->readNext();
    type = reader->readNext();
    QString rootName = reader->name().trimmed().toString();
    if(rootName.isEmpty() || rootName != "RespScheduleTaskDownloadStatus")
    {
        //不是中心收到节点下载任务状况回执给节点报文
        tsExcep.setType(Environment::Datagram::State::_3);
        tsExcep.setText(trs("未知报文类型"));
        throw tsExcep;
    }
    while(!reader->atEnd()) {
        type = reader->readNext();
        if (type == QXmlStreamReader::StartElement &&
                !reader->name().isEmpty()) {
            this->TaskReplyInfo::toEntity(reader);
        }
    }
    // 解析XML报文出错
    if (reader->hasError()) {
        tsExcep.setType(Environment::Datagram::State::_1);
        tsExcep.setText(QString("%1,%2").arg(trs("中心收到节点下载任务状况回执给节点解析报文出错 ")).arg(reader->errorString()));
        throw tsExcep;
    }
    //校验报文是否合法,合法才可使用
    validate(tsExcep);
}

void RespScheduleTaskDownloadStatus::validate(TransException &tsExcep)
{
    COMMON_VALIDATE(tsExcep,Sche_Data_Trans::RESPSCHEDULETASKDOWNLOADSTATUS);
    //...
}

quint8 RespScheduleTaskDownloadStatus::messageType() const
{
    return Sche_Data_Trans::RESPSCHEDULETASKDOWNLOADSTATUS;
}






