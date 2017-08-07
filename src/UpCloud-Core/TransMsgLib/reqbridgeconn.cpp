#include "reqbridgeconn.h"
using namespace Environment::Datagram;
ReqBridgeConn::ReqBridgeConn()
{
    PubKey.clear();
}
ReqBridgeConn::~ReqBridgeConn()
{

}

void ReqBridgeConn::toXML(QXmlStreamWriter *writer)
{
    TransException tsExcep;
    //校验实体是否合法,合法才可拼报文
    validate(tsExcep);
    //拼接报文
    writer->setAutoFormatting(true);
    writer->writeStartDocument();
    writer->writeStartElement("ReqBridgeConn");
    this->BasicInfo::toXML(writer);
    writer->writeTextElement(trs("PubKey"),PubKey);
    writer->writeTextElement(trs("PriKey"),PriKey);
    writer->writeTextElement(trs("MacAddr"),MacAddr);
    writer->writeEndElement();
    writer->writeEndDocument();
}

void ReqBridgeConn::toEntity(QXmlStreamReader *reader)
{
    TransException tsExcep;

    QXmlStreamReader::TokenType type = reader->readNext();
    type = reader->readNext();
    QString rootName = reader->name().trimmed().toString();
    if(rootName.isEmpty() || rootName != "ReqBridgeConn")
    {
        //不是节点向中心请求建立长连接报文
        tsExcep.setType(Environment::Datagram::State::_3);
        tsExcep.setText(trs("未知报文类型"));
        throw tsExcep;
    }

    while(!reader->atEnd()) {
        type = reader->readNext();
        if (type == QXmlStreamReader::StartElement &&
                !reader->name().isEmpty()) {
            rootName = reader->name().trimmed().toString();
            if(rootName=="PubKey")
            {
                reader->readNext();
                //如果不是文本,就提示报文拼错
                PubKey = reader->text().trimmed().toString();
            }
            else if(rootName=="PriKey")
            {
                reader->readNext();
                //如果不是文本,就提示报文拼错
                PriKey = reader->text().trimmed().toString();
            }
            else if(rootName=="MacAddr")
            {
                reader->readNext();
                //如果不是文本,就提示报文拼错
                MacAddr = reader->text().trimmed().toString();
            }
            else
            {
                this->BasicInfo::toEntity(reader);
            }
        }
    }
    // 解析XML报文出错
    if (reader->hasError()) {
        tsExcep.setType(Environment::Datagram::State::_1);
        tsExcep.setText(QString("%1,%2").arg(trs("节点向中心请求建立长连接解析报文出错")).arg(reader->errorString()));
        throw tsExcep;
    }
    //校验报文是否合法,合法才可使用
    validate(tsExcep);

}

void ReqBridgeConn::validate(TransException &tsExcep)
{
    COMMON_VALIDATE(tsExcep,Bridge_Conn::REQBRIDGECONN);
    //pubKey为空
    if(this->PubKey.isEmpty() == true)
    {
        tsExcep.setType(Environment::Datagram::Bridge_Conn::Req_Info_State::_11);                                \
        tsExcep.setText(Environment::Datagram::Bridge_Conn::Req_Info_State::_11_DESC_PubKeyIsEmpty);         \
        throw tsExcep;
    }
    //PriKey为空
    if(this->PriKey.isEmpty() == true)
    {
        tsExcep.setType(Environment::Datagram::Bridge_Conn::Req_Info_State::_12);                                \
        tsExcep.setText(Environment::Datagram::Bridge_Conn::Req_Info_State::_12_DESC_PriKeyIsEmpty);         \
        throw tsExcep;
    }
    //MacAddr为空
    if(this->MacAddr.isEmpty() == true)
    {
        tsExcep.setType(Environment::Datagram::Bridge_Conn::Req_Info_State::_13);                                \
        tsExcep.setText(Environment::Datagram::Bridge_Conn::Req_Info_State::_13_DESC_MacAddrIsEmpty);         \
        throw tsExcep;
    }
}

quint8 ReqBridgeConn::messageType() const
{
    return Bridge_Conn::REQBRIDGECONN;
}
