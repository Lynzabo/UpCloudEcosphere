#include "reqscheduletaskdownloadstatus.h"

using namespace Environment::Datagram;

ReqScheduleTaskDownloadStatus::ReqScheduleTaskDownloadStatus()
{

}

void ReqScheduleTaskDownloadStatus::toXML(QXmlStreamWriter *writer)
{
    TransException tsExcep;
    //校验实体是否合法,合法才可拼报文
    validate(tsExcep);
    //拼接报文
    writer->setAutoFormatting(true);
    writer->writeStartDocument();
    writer->writeStartElement("ReqScheduleTaskDownloadStatus");
    this->CommonFilesExecStatus::toXML(writer);
    writer->writeEndElement();
    writer->writeEndDocument();
}

void ReqScheduleTaskDownloadStatus::toEntity(QXmlStreamReader *reader)
{
    TransException tsExcep;

    QXmlStreamReader::TokenType type = reader->readNext();
    type = reader->readNext();
    QString rootName = reader->name().trimmed().toString();
    if(rootName.isEmpty() || rootName != "ReqScheduleTaskDownloadStatus")
    {
        //不是节点下载完成反馈下载任务状况给中心报文
        tsExcep.setType(Environment::Datagram::State::_3);
        tsExcep.setText(trs("未知报文类型"));
        throw tsExcep;
    }
    while(!reader->atEnd()) {
        type = reader->readNext();
        if (type == QXmlStreamReader::StartElement &&
                !reader->name().isEmpty()) {
            this->CommonFilesExecStatus::toEntity(reader);
        }
    }
    // 解析XML报文出错
    if (reader->hasError()) {
        tsExcep.setType(Environment::Datagram::State::_1);
        tsExcep.setText(QString("%1,%2").arg(trs("节点下载完成反馈下载任务状况给中心解析报文出错 ")).arg(reader->errorString()));
        throw tsExcep;
    }
    //校验报文是否合法,合法才可使用
    validate(tsExcep);
}

void ReqScheduleTaskDownloadStatus::validate(TransException &tsExcep)
{
    //报文类型为空
    if(this->MessageType==0)
    {
        tsExcep.setType(Environment::Datagram::State::_2);
        tsExcep.setText(trs("报文类型为空"));
        throw tsExcep;
    }
    //报文类型不匹配
    if(this->MessageType!=Sche_Data_Trans::REQSCHEDULETASKDOWNLOADSTATUS)
    {
        tsExcep.setType(Environment::Datagram::State::_3);
        tsExcep.setText(trs("未知报文类型"));
        throw tsExcep;
    }
    //...
}

quint8 ReqScheduleTaskDownloadStatus::messageType() const
{
    return Sche_Data_Trans::REQSCHEDULETASKDOWNLOADSTATUS;
}





