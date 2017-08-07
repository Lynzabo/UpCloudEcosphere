#include "requnstructfilesdownloadinfo.h"
using namespace Environment::Datagram;
ReqUnstructFilesDownloadInfo::ReqUnstructFilesDownloadInfo()
{

}

void ReqUnstructFilesDownloadInfo::toXML(QXmlStreamWriter *writer)
{
    TransException tsExcep;
    //校验实体是否合法,合法才可拼报文
    validate(tsExcep);
    //拼接报文
    writer->setAutoFormatting(true);    
    writer->writeStartDocument();
    writer->writeStartElement("ReqUnstructFilesDownloadInfo");
    this->CommonFilesDownloadInfo::toXML(writer);
    writer->writeEndElement();
    writer->writeEndDocument();
}

void ReqUnstructFilesDownloadInfo::toEntity(QXmlStreamReader *reader)
{
    TransException tsExcep;

    QXmlStreamReader::TokenType type = reader->readNext();
    type = reader->readNext();
    QString rootName = reader->name().trimmed().toString();
    if(rootName.isEmpty() || rootName != "ReqUnstructFilesDownloadInfo")
    {
        //不是中心分发非结构文件组报文
        tsExcep.setType(Environment::Datagram::State::_3);
        tsExcep.setText(trs("未知报文类型"));
        throw tsExcep;
    }
    while(!reader->atEnd()) {
        type = reader->readNext();
        if (type == QXmlStreamReader::StartElement &&
                !reader->name().isEmpty()) {            
            this->CommonFilesDownloadInfo::toEntity(reader);
        }
    }
    // 解析XML报文出错
    if (reader->hasError()) {
        tsExcep.setType(Environment::Datagram::State::_1);
        tsExcep.setText(QString("%1,%2").arg(trs("中心分发非结构文件组解析报文出错")).arg(reader->errorString()));
        throw tsExcep;
    }
    //校验报文是否合法,合法才可使用
    validate(tsExcep);
}

void ReqUnstructFilesDownloadInfo::validate(TransException &tsExcep)
{
    TASK_VALIDATE(tsExcep,Unstru_Data_Trans::REQUNSTRUCTFILESDOWNLOADINFO);
    //...
}

quint8 ReqUnstructFilesDownloadInfo::messageType() const
{
    return Unstru_Data_Trans::REQUNSTRUCTFILESDOWNLOADINFO;
}
