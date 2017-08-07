#include "respheartthrobsconn.h"

using namespace Environment::Datagram;

RespHeartthrobsConn::RespHeartthrobsConn()
{

}
RespHeartthrobsConn::~RespHeartthrobsConn()
{

}

void RespHeartthrobsConn::toXML(QXmlStreamWriter *writer)
{
    TransException tsExcep;
    //校验实体是否合法,合法才可拼报文
    validate(tsExcep);
    //拼接报文
    writer->setAutoFormatting(true);
    writer->writeStartDocument();
    writer->writeStartElement("RespHeartthrobsConn");
    this->ReplyInfo::toXML(writer);
    writer->writeEndElement();
    writer->writeEndDocument();
}

void RespHeartthrobsConn::toEntity(QXmlStreamReader *reader)
{
    TransException tsExcep;

    QXmlStreamReader::TokenType type = reader->readNext();
    type = reader->readNext();
    QString rootName = reader->name().trimmed().toString();
    if(rootName.isEmpty() || rootName != "RespHeartthrobsConn")
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
            this->ReplyInfo::toEntity(reader);
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

void RespHeartthrobsConn::validate(TransException &tsExcep)
{
    COMMON_VALIDATE(tsExcep,Heartthrob_Conn::RESPHEARTTHROBSCONN);
    //...
}

quint8 RespHeartthrobsConn::messageType() const
{
    return Heartthrob_Conn::RESPHEARTTHROBSCONN;
}


