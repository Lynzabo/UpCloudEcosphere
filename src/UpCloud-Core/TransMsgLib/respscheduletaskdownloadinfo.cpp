#include "respscheduletaskdownloadinfo.h"

using namespace Environment::Datagram;

RespScheduleTaskDownloadInfo::RespScheduleTaskDownloadInfo()
{

}

RespScheduleTaskDownloadInfo::~RespScheduleTaskDownloadInfo()
{

}

void RespScheduleTaskDownloadInfo::toXML(QXmlStreamWriter *writer)
{
    TransException tsExcep;
    //校验实体是否合法,合法才可拼报文
    validate(tsExcep);
    //拼接报文
    writer->setAutoFormatting(true);
    writer->writeStartDocument();
    writer->writeStartElement("RespScheduleTaskDownloadInfo");
    this->TaskReplyInfo::toXML(writer);
    writer->writeEndElement();
    writer->writeEndDocument();
}

void RespScheduleTaskDownloadInfo::toEntity(QXmlStreamReader *reader)
{
    TransException tsExcep;

    QXmlStreamReader::TokenType type = reader->readNext();
    type = reader->readNext();
    QString rootName = reader->name().trimmed().toString();
    if(rootName.isEmpty() || rootName != "RespScheduleTaskDownloadInfo")
    {
        //不是节点响应中心收到预执行任务文件组下载请求报文
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
        tsExcep.setText(QString("%1,%2").arg(trs("节点响应中心收到预执行任务文件组下载请求解析报文出错")).arg(reader->errorString()));
        throw tsExcep;
    }
    //校验报文是否合法,合法才可使用
    validate(tsExcep);
}

void RespScheduleTaskDownloadInfo::validate(TransException &tsExcep)
{
    COMMON_VALIDATE(tsExcep,Sche_Data_Trans::RESPSCHEDULETASKDOWNLOADINFO);
    //...
}

quint8 RespScheduleTaskDownloadInfo::messageType() const
{
    return Sche_Data_Trans::RESPSCHEDULETASKDOWNLOADINFO;
}




