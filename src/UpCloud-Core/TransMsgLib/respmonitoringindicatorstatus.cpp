#include "respmonitoringindicatorstatus.h"

using namespace Environment::Datagram;

RespMonitoringIndicatorStatus::RespMonitoringIndicatorStatus()
{

}

RespMonitoringIndicatorStatus::~RespMonitoringIndicatorStatus()
{

}

void RespMonitoringIndicatorStatus::toXML(QXmlStreamWriter *writer)
{
    TransException tsExcep;
    //校验实体是否合法,合法才可拼报文
    validate(tsExcep);
    //拼接报文
    writer->setAutoFormatting(true);
    writer->writeStartDocument();
    writer->writeStartElement("RespMonitoringIndicatorStatus");
    this->ReplyInfo::toXML(writer);
    writer->writeEndElement();
    writer->writeEndDocument();
}

void RespMonitoringIndicatorStatus::toEntity(QXmlStreamReader *reader)
{
    TransException tsExcep;

    QXmlStreamReader::TokenType type = reader->readNext();
    type = reader->readNext();
    QString rootName = reader->name().trimmed().toString();
    if(rootName.isEmpty() || rootName != "RespMonitoringIndicatorStatus")
    {
        //不是中心响应收到指标
        tsExcep.setType(Environment::Datagram::State::_3);
        tsExcep.setText(trs("未知报文类型"));
        throw tsExcep;
    }

    while(!reader->atEnd()) {
        type = reader->readNext();
        if (type == QXmlStreamReader::StartElement &&
                !reader->name().isEmpty()) {
            this->ReplyInfo::toEntity(reader);
        }
    }
    // 解析XML报文出错

    if (reader->hasError()) {
        tsExcep.setType(Environment::Datagram::State::_1);
        tsExcep.setText(QString("%1,%2").arg(trs("中心响应收到指标解析报文出错 ")).arg(reader->errorString()));
        throw tsExcep;
    }
    //校验报文是否合法,合法才可使用
    validate(tsExcep);

}

void RespMonitoringIndicatorStatus::validate(TransException &tsExcep)
{
    COMMON_VALIDATE(tsExcep,Monit_Ctrl::RESPMONITORINGINDICATORSTATUS);
    //...
}

quint8 RespMonitoringIndicatorStatus::messageType() const
{
    return Monit_Ctrl::RESPMONITORINGINDICATORSTATUS;
}



