#include "reqheartthrobsconn.h"

using namespace Environment::Datagram;

ReqHeartthrobsConn::ReqHeartthrobsConn()
{

}

ReqHeartthrobsConn::~ReqHeartthrobsConn()
{

}

void ReqHeartthrobsConn::toXML(QXmlStreamWriter *writer)
{
    TransException tsExcep;
    //校验实体是否合法,合法才可拼报文
    validate(tsExcep);
    //拼接报文
    writer->setAutoFormatting(true);
    writer->writeStartDocument();
    writer->writeStartElement("ReqHeartthrobsConn");
    this->BasicInfo::toXML(writer);
    writer->writeEndElement();
    writer->writeEndDocument();
}

void ReqHeartthrobsConn::toEntity(QXmlStreamReader *reader)
{
    TransException tsExcep;

    QXmlStreamReader::TokenType type = reader->readNext();
    type = reader->readNext();
    QString rootName = reader->name().trimmed().toString();
    if(rootName.isEmpty() || rootName != "ReqHeartthrobsConn")
    {
        //不是节点向中心请求心跳连接报文
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
        tsExcep.setText(QString("%1,%2").arg(trs("节点向中心请求心跳连接解析报文出错 ")).arg(reader->errorString()));
        throw tsExcep;
    }
    //校验报文是否合法,合法才可使用
    validate(tsExcep);

}

void ReqHeartthrobsConn::validate(TransException &tsExcep)
{
    COMMON_VALIDATE(tsExcep,Heartthrob_Conn::REQHEARTTHROBSCONN);
    //...
}

quint8 ReqHeartthrobsConn::messageType() const
{
    return Heartthrob_Conn::REQHEARTTHROBSCONN;
}
