#include "reqstructtaskexecstatus.h"

using namespace Environment::Datagram;

ReqStructTaskExecStatus::ReqStructTaskExecStatus()
{

}

void ReqStructTaskExecStatus::toXML(QXmlStreamWriter *writer)
{
    TransException tsExcep;
    //校验实体是否合法,合法才可拼报文
    validate(tsExcep);
    //拼接报文
    writer->setAutoFormatting(true);
    writer->writeStartDocument();
    writer->writeStartElement("ReqStructTaskExecStatus");
    this->CommonFilesExecStatus::toXML(writer);
    writer->writeEndElement();
    writer->writeEndDocument();
}

void ReqStructTaskExecStatus::toEntity(QXmlStreamReader *reader)
{
    TransException tsExcep;

    QXmlStreamReader::TokenType type = reader->readNext();
    type = reader->readNext();
    QString rootName = reader->name().trimmed().toString();
    if(rootName.isEmpty() || rootName != "ReqStructTaskExecStatus")
    {
        //不是节点解析数据文件状况反馈给中心报文
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
        tsExcep.setText(QString("%1,%2").arg(trs("节点解析数据文件状况反馈给中心解析报文出错 ")).arg(reader->errorString()));
        throw tsExcep;
    }
    //校验报文是否合法,合法才可使用
    validate(tsExcep);
}

void ReqStructTaskExecStatus::validate(TransException &tsExcep)
{
    COMMON_VALIDATE(tsExcep,Stru_Data_Trans::REQSTRUCTTASKEXECSTATUS);
    //...
}

quint8 ReqStructTaskExecStatus::messageType() const
{
    return Stru_Data_Trans::REQSTRUCTTASKEXECSTATUS;
}




