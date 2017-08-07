#include "respremoteuioperacentorconn.h"

using namespace Environment::Datagram;

RespRemoteUIOperaCentorConn::RespRemoteUIOperaCentorConn()
{

}
RespRemoteUIOperaCentorConn::~RespRemoteUIOperaCentorConn()
{

}

void RespRemoteUIOperaCentorConn::toXML(QXmlStreamWriter *writer)
{
    TransException tsExcep;
    //校验实体是否合法,合法才可拼报文
    validate(tsExcep);
    //拼接报文
    writer->setAutoFormatting(true);
    writer->writeStartDocument();
    writer->writeStartElement("RespRemoteUIOperaCentorConn");
    this->ReplyInfo::toXML(writer);
    writer->writeEndElement();
    writer->writeEndDocument();
}

void RespRemoteUIOperaCentorConn::toEntity(QXmlStreamReader *reader)
{
    TransException tsExcep;

    QXmlStreamReader::TokenType type = reader->readNext();
    type = reader->readNext();
    QString rootName = reader->name().trimmed().toString();
    if(rootName.isEmpty() || rootName != "RespRemoteUIOperaCentorConn")
    {
        //不是中心响应远程UI建立长连接状态报文
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
        tsExcep.setText(QString("%1,%2").arg(trs("中心响应远程UI建立长连接状态解析报文出错 ")).arg(reader->errorString()));
        throw tsExcep;
    }
    //校验报文是否合法,合法才可使用
    validate(tsExcep);

}

void RespRemoteUIOperaCentorConn::validate(TransException &tsExcep)
{
    COMMON_VALIDATE(tsExcep,UI_Ctrl::RESPREMOTEUIOPERACENTORCONN);
    //...
}

quint8 RespRemoteUIOperaCentorConn::messageType() const
{
    return UI_Ctrl::RESPREMOTEUIOPERACENTORCONN;
}




