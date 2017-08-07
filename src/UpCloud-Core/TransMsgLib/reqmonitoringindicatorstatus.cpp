#include "reqmonitoringindicatorstatus.h"

using namespace Environment::Datagram;

ReqMonitoringIndicatorStatus::ReqMonitoringIndicatorStatus()
{
    indicatorInfo = new IndicatorInfo;
}

ReqMonitoringIndicatorStatus::~ReqMonitoringIndicatorStatus()
{
    delete indicatorInfo;
}

void ReqMonitoringIndicatorStatus::toXML(QXmlStreamWriter *writer)
{
    TransException tsExcep;
    //校验实体是否合法,合法才可拼报文
    validate(tsExcep);
    //拼接报文
    writer->setAutoFormatting(true);
    writer->writeStartDocument();
    writer->writeStartElement("ReqMonitoringIndicatorStatus");
    this->MonitoringIndicatorInfo::toXML(writer);
    if(indicatorInfo->Indicators.size() > 0)
    {
        writer->writeStartElement("IndicatorInfo");
        indicatorInfo->toXML(writer);
        writer->writeEndElement();
    }
    writer->writeEndElement();
    writer->writeEndDocument();
}

void ReqMonitoringIndicatorStatus::toEntity(QXmlStreamReader *reader)
{
    TransException tsExcep;

    QXmlStreamReader::TokenType type = reader->readNext();
    type = reader->readNext();
    QString rootName = reader->name().trimmed().toString();
    if(rootName.isEmpty() || rootName != "ReqMonitoringIndicatorStatus")
    {
        //不是节点发送指标给中心
        tsExcep.setType(Environment::Datagram::State::_3);
        tsExcep.setText(trs("未知报文类型"));
        throw tsExcep;
    }

    while(!reader->atEnd()) {
        type = reader->readNext();
        if (type == QXmlStreamReader::StartElement &&
                !reader->name().isEmpty()) {
            rootName = reader->name().trimmed().toString();
            if(rootName == "Indicators")
            {
                indicatorInfo->toEntity(reader);
            }
            else
            {
                this->MonitoringIndicatorInfo::toEntity(reader);
            }
        }
    }
    // 解析XML报文出错
    if (reader->hasError()) {
        tsExcep.setType(Environment::Datagram::State::_1);
        tsExcep.setText(QString("%1,%2").arg(trs("中心发起获取节点指标解析报文出错 ")).arg(reader->errorString()));
        throw tsExcep;
    }
    //校验报文是否合法,合法才可使用
    validate(tsExcep);
}

void ReqMonitoringIndicatorStatus::validate(TransException &tsExcep)
{
    COMMON_VALIDATE(tsExcep,Monit_Ctrl::REQMONITORINGINDICATORSTATUS);
    //...
}

quint8 ReqMonitoringIndicatorStatus::messageType() const
{
    return Monit_Ctrl::REQMONITORINGINDICATORSTATUS;
}







