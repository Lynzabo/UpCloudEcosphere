#include "respstructtaskexecstatus.h"

using namespace Environment::Datagram;

RespStructTaskExecStatus::RespStructTaskExecStatus()
{

}

RespStructTaskExecStatus::~RespStructTaskExecStatus()
{

}
void RespStructTaskExecStatus::toXML(QXmlStreamWriter *writer)
{
    TransException tsExcep;
    //校验实体是否合法,合法才可拼报文
    validate(tsExcep);
    //拼接报文
    writer->setAutoFormatting(true);
    writer->writeStartDocument();
    writer->writeStartElement("RespStructTaskExecStatus");
    this->TaskReplyInfo::toXML(writer);
    writer->writeEndElement();
    writer->writeEndDocument();
}

void RespStructTaskExecStatus::toEntity(QXmlStreamReader *reader)
{
    TransException tsExcep;

    QXmlStreamReader::TokenType type = reader->readNext();
    type = reader->readNext();
    QString rootName = reader->name().trimmed().toString();
    if(rootName.isEmpty() || rootName != "RespStructTaskExecStatus")
    {
        //不是中心收到节点解析数据文件状况回执给节点报文
        tsExcep.setType(Environment::Datagram::State::_3);
        tsExcep.setText(trs("未知报文类型"));
        throw tsExcep;
    }
    while(!reader->atEnd()) {
        type = reader->readNext();
        if (type == QXmlStreamReader::StartElement &&
                !reader->name().isEmpty()) {
            this->TaskReplyInfo::toEntity(reader);
        }
    }
    // 解析XML报文出错
    if (reader->hasError()) {
        tsExcep.setType(Environment::Datagram::State::_1);
        tsExcep.setText(QString("%1,%2").arg(trs("中心收到节点解析数据文件状况回执给节点解析报文出错 ")).arg(reader->errorString()));
        throw tsExcep;
    }
    //校验报文是否合法,合法才可使用
    validate(tsExcep);
}

void RespStructTaskExecStatus::validate(TransException &tsExcep)
{
    COMMON_VALIDATE(tsExcep,Stru_Data_Trans::RESPSTRUCTTASKEXECSTATUS);
    //...
}

quint8 RespStructTaskExecStatus::messageType() const
{
    return Stru_Data_Trans::RESPSTRUCTTASKEXECSTATUS;
}




