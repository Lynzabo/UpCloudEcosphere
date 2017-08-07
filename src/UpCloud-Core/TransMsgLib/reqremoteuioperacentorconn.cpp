#include "reqremoteuioperacentorconn.h"

using namespace Environment::Datagram;

ReqRemoteUIOperaCentorConn::ReqRemoteUIOperaCentorConn()
{

}



ReqRemoteUIOperaCentorConn::~ReqRemoteUIOperaCentorConn()
{

}

void ReqRemoteUIOperaCentorConn::toXML(QXmlStreamWriter *writer)
{
    TransException tsExcep;
    //校验实体是否合法,合法才可拼报文
    validate(tsExcep);
    //拼接报文
    writer->setAutoFormatting(true);
    writer->writeStartDocument();
    writer->writeStartElement("ReqRemoteUIOperaCentorConn");
    this->BasicInfo::toXML(writer);
    writer->writeEndElement();
    writer->writeEndDocument();
}

void ReqRemoteUIOperaCentorConn::toEntity(QXmlStreamReader *reader)
{
    TransException tsExcep;

    QXmlStreamReader::TokenType type = reader->readNext();
    type = reader->readNext();
    QString rootName = reader->name().trimmed().toString();
    if(rootName.isEmpty() || rootName != "ReqRemoteUIOperaCentorConn")
    {
        //不是远程UI客户端请求中心建立长连接
        tsExcep.setType(Environment::Datagram::State::_3);
        tsExcep.setText(trs("未知报文类型"));
        throw tsExcep;
    }

    while(!reader->atEnd()) {
        type = reader->readNext();
        if (type == QXmlStreamReader::StartElement &&
                !reader->name().isEmpty()) {
            this->BasicInfo::toEntity(reader);
        }
    }
    // 解析XML报文出错
    if (reader->hasError()) {
        tsExcep.setType(Environment::Datagram::State::_1);
        tsExcep.setText(QString("%1,%2").arg(trs("远程UI客户端请求中心建立长连接解析报文出错 ")).arg(reader->errorString()));
        throw tsExcep;
    }
    //校验报文是否合法,合法才可使用
    validate(tsExcep);

}

void ReqRemoteUIOperaCentorConn::validate(TransException &tsExcep)
{
    COMMON_VALIDATE(tsExcep,UI_Ctrl::REQREMOTEUIOPERACENTORCONN);
    //...
}

quint8 ReqRemoteUIOperaCentorConn::messageType() const
{
    return UI_Ctrl::REQREMOTEUIOPERACENTORCONN;
}
