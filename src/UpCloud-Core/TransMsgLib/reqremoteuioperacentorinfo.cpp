#include "reqremoteuioperacentorinfo.h"

using namespace Environment::Datagram;

ReqRemoteUIOperaCentorInfo::ReqRemoteUIOperaCentorInfo()
{

}

ReqRemoteUIOperaCentorInfo::~ReqRemoteUIOperaCentorInfo()
{

}

void ReqRemoteUIOperaCentorInfo::toXML(QXmlStreamWriter *writer)
{
    TransException tsExcep;
    //校验实体是否合法,合法才可拼报文
    validate(tsExcep);
    //拼接报文
    writer->setAutoFormatting(true);
    writer->writeStartDocument();
    writer->writeStartElement("ReqRemoteUIOperaCentorInfo");
    this->RemoteOperaBaseInfo::toXML(writer);
    writer->writeEndElement();
    writer->writeEndDocument();
}

void ReqRemoteUIOperaCentorInfo::toEntity(QXmlStreamReader *reader)
{
    TransException tsExcep;

    QXmlStreamReader::TokenType type = reader->readNext();
    type = reader->readNext();
    QString rootName = reader->name().trimmed().toString();
    if(rootName.isEmpty() || rootName != "ReqRemoteUIOperaCentorInfo")
    {
        //不是远程UI请求中心操作数据
        tsExcep.setType(Environment::Datagram::State::_3);
        tsExcep.setText(trs("未知报文类型"));
        throw tsExcep;
    }

    while(!reader->atEnd()) {
        type = reader->readNext();
        if (type == QXmlStreamReader::StartElement &&
                !reader->name().isEmpty()) {
            this->RemoteOperaBaseInfo::toEntity(reader);
        }
    }
    // 解析XML报文出错
    if (reader->hasError()) {
        tsExcep.setType(Environment::Datagram::State::_1);
        tsExcep.setText(QString("%1,%2").arg(trs("远程UI请求中心操作数据解析报文出错 ")).arg(reader->errorString()));
        throw tsExcep;
    }
    //校验报文是否合法,合法才可使用
    validate(tsExcep);

}

void ReqRemoteUIOperaCentorInfo::validate(TransException &tsExcep)
{
    COMMON_VALIDATE(tsExcep,UI_Ctrl::REQREMOTEUIOPERACENTORINFO);
    //...
}

quint8 ReqRemoteUIOperaCentorInfo::messageType() const
{
    return UI_Ctrl::REQREMOTEUIOPERACENTORINFO;
}

