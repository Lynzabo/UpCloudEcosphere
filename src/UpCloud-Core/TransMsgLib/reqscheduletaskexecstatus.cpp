#include "reqscheduletaskexecstatus.h"

using namespace Environment::Datagram;

ReqScheduleTaskExecStatus::ReqScheduleTaskExecStatus()
{

}

void ReqScheduleTaskExecStatus::toXML(QXmlStreamWriter *writer)
{
    TransException tsExcep;
    //校验实体是否合法,合法才可拼报文
    validate(tsExcep);
    //拼接报文
    writer->setAutoFormatting(true);
    writer->writeStartDocument();
    writer->writeStartElement("ReqScheduleTaskExecStatus");
    this->CommonFilesExecStatus::toXML(writer);
    writer->writeEndElement();
    writer->writeEndDocument();
}

void ReqScheduleTaskExecStatus::toEntity(QXmlStreamReader *reader)
{
    TransException tsExcep;

    QXmlStreamReader::TokenType type = reader->readNext();
    type = reader->readNext();
    QString rootName = reader->name().trimmed().toString();
    if(rootName.isEmpty() || rootName != "ReqScheduleTaskExecStatus")
    {
        //不是节点执行任务状况反馈给中心报文
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
        tsExcep.setText(QString("%1,%2").arg(trs("节点执行任务状况反馈给中心解析报文出错 ")).arg(reader->errorString()));
        throw tsExcep;
    }
    //校验报文是否合法,合法才可使用
    validate(tsExcep);
}

void ReqScheduleTaskExecStatus::validate(TransException &tsExcep)
{
    COMMON_VALIDATE(tsExcep,Sche_Data_Trans::REQSCHEDULETASKEXECSTATUS);
    //...
}

quint8 ReqScheduleTaskExecStatus::messageType() const
{
    return Sche_Data_Trans::REQSCHEDULETASKEXECSTATUS;
}






