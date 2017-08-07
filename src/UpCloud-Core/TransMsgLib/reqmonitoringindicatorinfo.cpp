#include "reqmonitoringindicatorinfo.h"

using namespace Environment::Datagram;

ReqMonitoringIndicatorInfo::ReqMonitoringIndicatorInfo()
{

}

ReqMonitoringIndicatorInfo::~ReqMonitoringIndicatorInfo()
{

}

void ReqMonitoringIndicatorInfo::toXML(QXmlStreamWriter *writer)
{
    TransException tsExcep;
    //校验实体是否合法,合法才可拼报文
    validate(tsExcep);
    //拼接报文
    writer->setAutoFormatting(true);
    writer->writeStartDocument();
    writer->writeStartElement("ReqMonitoringIndicatorInfo");
    this->MonitoringIndicatorInfo::toXML(writer);
    writer->writeEndElement();
    writer->writeEndDocument();
}

void ReqMonitoringIndicatorInfo::toEntity(QXmlStreamReader *reader)
{
    TransException tsExcep;

    QXmlStreamReader::TokenType type = reader->readNext();
    type = reader->readNext();
    QString rootName = reader->name().trimmed().toString();
    if(rootName.isEmpty() || rootName != "ReqMonitoringIndicatorInfo")
    {
        //不是中心发起获取节点指标
        tsExcep.setType(Environment::Datagram::State::_3);
        tsExcep.setText(trs("未知报文类型"));
        throw tsExcep;
    }

    while(!reader->atEnd()) {
        type = reader->readNext();
        if (type == QXmlStreamReader::StartElement &&
                !reader->name().isEmpty()) {
            this->MonitoringIndicatorInfo::toEntity(reader);
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

void ReqMonitoringIndicatorInfo::validate(TransException &tsExcep)
{
    COMMON_VALIDATE(tsExcep,Monit_Ctrl::REQMONITORINGINDICATORINFO);
    //...
}

quint8 ReqMonitoringIndicatorInfo::messageType() const
{
    return Monit_Ctrl::REQMONITORINGINDICATORINFO;
}


