#include "respbridgeconn.h"

using namespace Environment::Datagram;

RespBridgeConn::RespBridgeConn()
{
    PubKey = 0;
}
RespBridgeConn::~RespBridgeConn()
{

}

void RespBridgeConn::toXML(QXmlStreamWriter *writer)
{
    TransException tsExcep;
    //校验实体是否合法,合法才可拼报文
    validate(tsExcep);
    //拼接报文
    writer->setAutoFormatting(true);
    writer->writeStartDocument();
    writer->writeStartElement("RespBridgeConn");
    this->ReplyInfo::toXML(writer);
    writer->writeTextElement(trs("PubKey"),QString("%1").arg(PubKey));
    writer->writeEndElement();
    writer->writeEndDocument();
}

void RespBridgeConn::toEntity(QXmlStreamReader *reader)
{
    TransException tsExcep;

    QXmlStreamReader::TokenType type = reader->readNext();
    type = reader->readNext();
    QString rootName = reader->name().trimmed().toString();
    if(rootName.isEmpty() || rootName != "RespBridgeConn")
    {
        //不是中心响应节点收到长连接报文
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
                QString text = reader->text().trimmed().toString();
                PubKey = text.toUInt();
            }
            else
            {
                this->ReplyInfo::toEntity(reader);
            }
        }
    }
    // 解析XML报文出错

    if (reader->hasError()) {
        tsExcep.setType(Environment::Datagram::State::_1);
        tsExcep.setText(QString("%1,%2").arg(trs("中心响应节点收到长连接解析报文出错 ")).arg(reader->errorString()));
        throw tsExcep;
    }
    //校验报文是否合法,合法才可使用
    validate(tsExcep);

}

void RespBridgeConn::validate(TransException &tsExcep)
{
    COMMON_VALIDATE(tsExcep,Bridge_Conn::RESPBRIDGECONN);
    //...
}

quint8 RespBridgeConn::messageType() const
{
    return Bridge_Conn::RESPBRIDGECONN;
}
