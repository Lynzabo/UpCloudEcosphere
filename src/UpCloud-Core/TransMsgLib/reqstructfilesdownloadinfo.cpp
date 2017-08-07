#include "reqstructfilesdownloadinfo.h"

using namespace Environment::Datagram;

ReqStructFilesDownloadInfo::ReqStructFilesDownloadInfo()
{

}

void ReqStructFilesDownloadInfo::toXML(QXmlStreamWriter *writer)
{
    TransException tsExcep;
    //校验实体是否合法,合法才可拼报文
    validate(tsExcep);
    //拼接报文
    writer->setAutoFormatting(true);
    writer->writeStartDocument();
    writer->writeStartElement("ReqStructFilesDownloadInfo");
    this->CommonFilesExecInfo::toXML(writer);
    writer->writeEndElement();
    writer->writeEndDocument();
}

void ReqStructFilesDownloadInfo::toEntity(QXmlStreamReader *reader)
{
    TransException tsExcep;

    QXmlStreamReader::TokenType type = reader->readNext();
    type = reader->readNext();
    QString rootName = reader->name().trimmed().toString();
    if(rootName.isEmpty() || rootName != "ReqStructFilesDownloadInfo")
    {
        //不是中心分发结构文件组报文
        tsExcep.setType(Environment::Datagram::State::_3);
        tsExcep.setText(Environment::Datagram::State::_3_DESC_DatagramUnmatched);
        throw tsExcep;
    }
    while(!reader->atEnd()) {
        type = reader->readNext();
        if (type == QXmlStreamReader::StartElement &&
                !reader->name().isEmpty()) {
            this->CommonFilesExecInfo::toEntity(reader);
        }
    }
    // 解析XML报文出错
    if (reader->hasError()) {
        tsExcep.setType(Environment::Datagram::State::_1);
        tsExcep.setText(QString("%1,%2").arg(trs("中心分发结构文件组解析报文出错 ")).arg(reader->errorString()));
        throw tsExcep;
    }
    //校验报文是否合法,合法才可使用
    validate(tsExcep);
}

void ReqStructFilesDownloadInfo::validate(TransException &tsExcep)
{
    TASK_VALIDATE(tsExcep,Stru_Data_Trans::REQSTRUCTFILESDOWNLOADINFO);
    using namespace Environment::Datagram::Stru_Data_Trans;
    QString exectime = this->ExecTime;
    //执行时间是否为空
    if(exectime.isEmpty())
    {
        tsExcep.setType(Resp_Info_State::_8);
        tsExcep.setText(Resp_Info_State::_8_DESC_ExecTimeIsNull);
        throw tsExcep;
    }
    //执行时间是否为合法
    QString newExectime;
    try{
        TimerUtil::format(exectime, newExectime);
        this->ExecTime = newExectime;
    }
    catch(QString &formatExcep)
    {
        Q_UNUSED(formatExcep);
        tsExcep.setType(Resp_Info_State::_9);
        tsExcep.setText(Resp_Info_State::_9_DESC_ExecTimeFormatError);
        throw tsExcep;
    }
    catch(...)
    {
    }
    //...
}

quint8 ReqStructFilesDownloadInfo::messageType() const
{
    return Stru_Data_Trans::REQSTRUCTFILESDOWNLOADINFO;
}


