#include "respremoteuioperacentorinfo.h"

using namespace Environment::Datagram;

RespRemoteUIOperaCentorInfo::RespRemoteUIOperaCentorInfo()
{
    State = 0;
    Content = "";
}

RespRemoteUIOperaCentorInfo::~RespRemoteUIOperaCentorInfo()
{

}

void RespRemoteUIOperaCentorInfo::toXML(QXmlStreamWriter *writer)
{
    TransException tsExcep;
    //校验实体是否合法,合法才可拼报文
    validate(tsExcep);
    //拼接报文
    writer->setAutoFormatting(true);
    writer->writeStartDocument();
    writer->writeStartElement("RespRemoteUIOperaCentorInfo");
    this->RemoteOperaBaseInfo::toXML(writer);
    writer->writeTextElement(trs("State"),QString("%1").arg(State));
    writer->writeTextElement(trs("Content"),QString("%1").arg(Content));
    writer->writeEndElement();
    writer->writeEndDocument();
}

void RespRemoteUIOperaCentorInfo::toEntity(QXmlStreamReader *reader)
{
    TransException tsExcep;

    QXmlStreamReader::TokenType type = reader->readNext();
    type = reader->readNext();
    QString rootName = reader->name().trimmed().toString();
    if(rootName.isEmpty() || rootName != "RespRemoteUIOperaCentorInfo")
    {
        //不是中心返回远程UI请求数据报文
        tsExcep.setType(Environment::Datagram::State::_3);
        tsExcep.setText(trs("未知报文类型"));
        throw tsExcep;
    }

    while(!reader->atEnd()) {
        type = reader->readNext();
        if (type == QXmlStreamReader::StartElement &&
                !reader->name().isEmpty()) {
            rootName = reader->name().trimmed().toString();
            if(rootName=="State")
            {
                reader->readNext();
                QString text = reader->text().trimmed().toString();
                State = (quint8)text.toUInt();
            }
            else if(rootName=="Content")
            {
                reader->readNext();
                QString text = reader->text().trimmed().toString();
                Content = text;
            }
            else
            {
                this->RemoteOperaBaseInfo::toEntity(reader);
            }
        }
    }
    // 解析XML报文出错

    if (reader->hasError()) {
        tsExcep.setType(Environment::Datagram::State::_1);
        tsExcep.setText(QString("%1,%2").arg(trs("中心返回远程UI请求数据解析报文出错 ")).arg(reader->errorString()));
        throw tsExcep;
    }
    //校验报文是否合法,合法才可使用
    validate(tsExcep);

}

void RespRemoteUIOperaCentorInfo::validate(TransException &tsExcep)
{
    COMMON_VALIDATE(tsExcep,UI_Ctrl::RESPREMOTEUIOPERACENTORINFO);
    //...
}

quint8 RespRemoteUIOperaCentorInfo::messageType() const
{
    return UI_Ctrl::RESPREMOTEUIOPERACENTORINFO;
}




