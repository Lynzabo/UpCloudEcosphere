//////////////////////////////////////////////////////////////////测试报文装帧和解帧
//#include <QCoreApplication>
//#include <QtCore>
//#include "transmsg.h"
///**
// * @brief CallbackByReqBridgeConn   解析报文体回调
// * @param req
// * Notice:使用完后要释放这个指针
// */
//void CallbackByReqBridgeConn(ReqBridgeConn *req)
//{
//    qDebug() << "ReqBridgeConn:" << req->UUID;
//    delete req;
//}
///**
// * @brief CallbackByDatagramInfo    解析报文装帧格式回调
// * @param gram
//    * Notice:使用完后要释放这个指针
// */
//void CallbackByDatagramInfo(DataGramInfo *gram)
//{
//    qDebug() << "DataGramInfo:" << gram->requestID;
//    delete gram;
//}
//int main(int argc, char *argv[])
//{
//    //注册系统日志自定义格式监听器
//    //Logger::registerSystemLogger();

//    QCoreApplication app( argc, argv );

//    //生成报文并进行装帧
//    ReqBridgeConn req;
//    req.PubKey = 0x12345678;
//    QByteArray data;
//    try
//    {
//        DatagramUtil::getInstance().packDatagram(&req,data);
//    }
//    catch(QString &excep)
//    {
//        qDebug() << trs("出错:%1").arg(excep);
//        return 0;
//    }
//    catch(TransException &excep)
//    {
//       qDebug() << excep.getText();
//       return 0;
//    }
//    qDebug() << trs("报文长度:") << data.size();
//    //解帧报文并生成报文实体
//    try
//    {
//        DatagramUtil::getInstance().parseDatagram(CallbackByDatagramInfo,CallbackByReqBridgeConn,data);
//    }
//    catch(QString &excep)
//    {
//        qDebug() << trs("出错:%1").arg(excep);
//        return 0;
//    }
//    catch(TransException &excep)
//    {
//       qDebug() << excep.getText();
//       return 0;
//    }
//    return app.exec();
//}

/////////////////////////////////////////////////////////////1.非结构化报文读取和生成测试
/*
#include <QCoreApplication>
#include <QtCore>
#include "requnstructfilesdownloadinfo.h"
int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    ReqUnstructFilesDownloadInfo req;

    req.MessageType = 0x4;
    req.UUID = 15101010;
    req.RequestID = 0x1;
    req.TaskUUID=432432432432;
    req.TaskExecType = 1;
    req.Strategy = 1;
    FileDownload *fd = new FileDownload;
    fd->DownloadURLs = "ftp://ip:port/project/111.txt";
    fd->DescPath = "d:/111.txt";
    FileDownload *fd2 = new FileDownload;
    fd2->DownloadURLs = "ftp://ip:port/project/222.txt";
    fd2->DescPath = "d:/222.txt";
    req.ftpPush->IP = "127.0.0.1";
    req.ftpPush->Port = 21;
    req.ftpPush->Username = "user01";
    req.ftpPush->Password = "pwd01";
    req.ftpPush->FilesDownloadURLs.append(fd);
    req.ftpPush->FilesDownloadURLs.append(fd2);

    FileDownload *fd3 = new FileDownload;
    fd3->DownloadURLs = "http://ip:port/project/111.txt";
    fd3->DescPath = "d:/111.txt";
    FileDownload *fd4 = new FileDownload;
    fd4->DownloadURLs = "http://ip:port/project/222.txt";
    fd4->DescPath = "d:/222.txt";
    req.httpPush->FilesDownloadURLs.append(fd3);
    req.httpPush->FilesDownloadURLs.append(fd4);

    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    ReqUnstructFilesDownloadInfo req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test RespRemoteUIOperaCentorInfo
#include <QCoreApplication>
#include <QtCore>
#include "respremoteuioperacentorinfo.h"

int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );
    quint64 tim = TimerUtil::currentTimeMillis();
    QString time;
    TimerUtil::quint64ToQString(tim,time);
    qDebug() << tim << ":" << time;
    //生成报文
    RespRemoteUIOperaCentorInfo req;
    req.MessageType = 0x1C;
    req.UUID = 15101010;
    req.RequestID = 0xF;
    req.ExecType = 0x11;
    req.Params = "arg1/arg2/arg3/arg4";
    req.State = 12;
    req.Content = "res1/res2/res3/res4";


    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    RespRemoteUIOperaCentorInfo req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }

    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test ReqRemoteUIOperaCentorInfo
#include <QCoreApplication>
#include <QtCore>
#include "reqremoteuioperacentorinfo.h"

int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    ReqRemoteUIOperaCentorInfo req;
    req.MessageType = 0x1B;
    req.UUID = 15101010;
    req.RequestID = 0xF;
    req.ExecType = 0x11;
    req.Params = "arg1/arg2/arg3/arg4";


    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    ReqRemoteUIOperaCentorInfo req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }

    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test RespRemoteUIOperaCentorConn
#include <QCoreApplication>
#include <QtCore>
#include "respremoteuioperacentorconn.h"

int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    RespRemoteUIOperaCentorConn req;
    req.MessageType = 0x1A;
    req.UUID = 15101010;
    req.RequestID = 0xF;
    req.State = 0x19;


    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    RespRemoteUIOperaCentorConn req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }

    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test ReqRemoteUIOperaCentorConn
#include <QCoreApplication>
#include <QtCore>
#include "reqremoteuioperacentorconn.h"

int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    ReqRemoteUIOperaCentorConn req;
    req.MessageType = 0x19;
    req.UUID = 15101010;
    req.RequestID = 0xF;


    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    ReqRemoteUIOperaCentorConn req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }

    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test RespMonitoringIndicatorStatus
#include <QCoreApplication>
#include <QtCore>
#include "respmonitoringindicatorstatus.h"

int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    RespMonitoringIndicatorStatus req;
    req.MessageType = 0x18;
    req.UUID = 15101010;
    req.RequestID = 0xF;
    req.State = 0x77;

    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    RespMonitoringIndicatorStatus req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }

    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test ReqMonitoringIndicatorStatus
#include <QCoreApplication>
#include <QtCore>
#include "reqmonitoringindicatorstatus.h"

int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    ReqMonitoringIndicatorStatus req;
    req.MessageType = 0x17;
    req.UUID = 15101010;
    req.RequestID = 0xF;
    req.IndicatorType = 0x77;

    Indicator *in = new Indicator;
    in->IndicatorKey = 0x11;
    in->IndicatorValue = "IndicatorValue111222";
    Indicator *in2 = new Indicator;
    in2->IndicatorKey = 0x22;
    in2->IndicatorValue = "IndicatorValue222111";
    req.indicatorInfo->Indicators.append(in);
    req.indicatorInfo->Indicators.append(in2);;


    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    ReqMonitoringIndicatorStatus req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }

    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test RespMonitoringIndicatorInfo
#include <QCoreApplication>
#include <QtCore>
#include "respmonitoringindicatorinfo.h"

int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    RespMonitoringIndicatorInfo req;
    req.MessageType = 0x16;
    req.UUID = 15101010;
    req.RequestID = 0xF;
    req.State = 13;


    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    RespMonitoringIndicatorInfo req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }

    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test ReqMonitoringIndicatorInfo
#include <QCoreApplication>
#include <QtCore>
#include "reqmonitoringindicatorinfo.h"

int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    ReqMonitoringIndicatorInfo req;
    req.MessageType = 0x15;
    req.UUID = 15101010;
    req.RequestID = 0xF;
    req.IndicatorType = 333;


    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    ReqMonitoringIndicatorInfo req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }

    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test RespScheduleTaskExecStatus
#include <QCoreApplication>
#include <QtCore>
#include "respscheduletaskexecstatus.h"

int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    RespScheduleTaskExecStatus req;
    req.MessageType = 0x14;
    req.UUID = 15101010;
    req.RequestID = 0xF;
    req.TaskUUID = 0x12345678;
    req.State = 17;


    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    RespScheduleTaskExecStatus req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }

    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test ReqScheduleTaskExecStatus
#include <QCoreApplication>
#include <QtCore>
#include "reqscheduletaskexecstatus.h"

int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    ReqScheduleTaskExecStatus req;
    req.MessageType = 0x13;
    req.UUID = 15101010;
    req.RequestID = 0xF;
    req.TaskUUID = 0x12345678;
    req.State = 77;
    req.Strategy = 608;

    Error *er = new Error;
    er->DownloadURLs = "ftp://ip:port/project/111.txt";
    er->ErrorMsg = "ErrMsg111222";
    Error *er2 = new Error;
    er2->DownloadURLs = "ftp://ip:port/project/222.txt";
    er2->ErrorMsg = "ErrMsg2221111";
    req.errorinfo->Errors.append(er);
    req.errorinfo->Errors.append(er2);;


    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    ReqScheduleTaskExecStatus req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }

    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test RespScheduleTaskDownloadStatus
#include <QCoreApplication>
#include <QtCore>
#include "respscheduletaskdownloadstatus.h"

int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    RespScheduleTaskDownloadStatus req;
    req.MessageType = 0x12;
    req.UUID = 15101010;
    req.RequestID = 0x1;
    req.TaskUUID = 0x12345678;
    req.State = 91;

    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    RespScheduleTaskDownloadStatus req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }

    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test ReqScheduleTaskDownloadStatus
#include <QCoreApplication>
#include <QtCore>
#include "reqscheduletaskdownloadstatus.h"

int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    ReqScheduleTaskDownloadStatus req;
    req.MessageType = 0x11;
    req.UUID = 15101010;
    req.RequestID = 0x1;
    req.TaskUUID = 0x12345678;
    req.State = 98;
    req.Strategy = 678;

    Error *er = new Error;
    er->DownloadURLs = "ftp://ip:port/project/111.txt";
    er->ErrorMsg = "ErrMsg111";
    Error *er2 = new Error;
    er2->DownloadURLs = "ftp://ip:port/project/222.txt";
    er2->ErrorMsg = "ErrMsg222";
    req.errorinfo->Errors.append(er);
    req.errorinfo->Errors.append(er2);;


    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    ReqScheduleTaskDownloadStatus req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }

    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test RespScheduleTaskDownloadInfo
#include <QCoreApplication>
#include <QtCore>
#include "respscheduletaskdownloadinfo.h"

int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    RespScheduleTaskDownloadInfo req;
    req.MessageType = 0x10;
    req.UUID = 15101010;
    req.RequestID = 0x1;
    req.TaskUUID = 0x12345678;
    req.State = 20;


    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    RespScheduleTaskDownloadInfo req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }

    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test ReqScheduleTaskDownloadInfo
#include <QCoreApplication>
#include <QtCore>
#include "reqscheduletaskdownloadinfo.h"

int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    ReqScheduleTaskDownloadInfo req;

    req.MessageType = 0xF;
    req.UUID = 15101010;
    req.RequestID = 0x1;
    req.TaskUUID = 0x12345678;
    req.TaskExecType = 99;
    req.Strategy = 555;
    req.setExecTime("20150813161015");
    req.EntranceFile = "entrance_file_11111";

    FileDownload *fd = new FileDownload;
    fd->DownloadURLs = "ftp://ip:port/project/111.txt";
    fd->DescPath = "d:/111.txt";
    FileDownload *fd2 = new FileDownload;
    fd2->DownloadURLs = "ftp://ip:port/project/222.txt";
    fd2->DescPath = "d:/222.txt";
    req.ftpPush->IP = "127.0.0.1";
    req.ftpPush->Port = 21;
    req.ftpPush->Username = "user01";
    req.ftpPush->Password = "pwd01";
    req.ftpPush->FilesDownloadURLs.append(fd);
    req.ftpPush->FilesDownloadURLs.append(fd2);

    FileDownload *fd3 = new FileDownload;
    fd3->DownloadURLs = "http://ip:port/project/111.txt";
    fd3->DescPath = "d:/111.txt";
    FileDownload *fd4 = new FileDownload;
    fd4->DownloadURLs = "http://ip:port/project/222.txt";
    fd4->DescPath = "d:/222.txt";
    req.httpPush->FilesDownloadURLs.append(fd3);
    req.httpPush->FilesDownloadURLs.append(fd4);



    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    ReqScheduleTaskDownloadInfo req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }

    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test RespStructTaskExecStatus
#include <QCoreApplication>
#include <QtCore>
#include "respstructtaskexecstatus.h"

int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    RespStructTaskExecStatus req;

    req.MessageType = 0xE;
    req.UUID = 15101010;
    req.RequestID = 0x1;
    req.TaskUUID = 0x12345678;
    req.State = 98;


    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    RespStructTaskExecStatus req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }

    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test ReqStructTaskExecStatus
#include <QCoreApplication>
#include <QtCore>
#include "reqstructtaskexecstatus.h"

int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    ReqStructTaskExecStatus req;

    req.MessageType = 0xD;
    req.UUID = 15101010;
    req.RequestID = 0x1;
    req.TaskUUID = 0x12345678;
    req.State = 98;
    req.Strategy = 678;

    Error *er = new Error;
    er->DownloadURLs = "ftp://ip:port/project/111.txt";
    er->ErrorMsg = "ErrMsg111";
    Error *er2 = new Error;
    er2->DownloadURLs = "ftp://ip:port/project/222.txt";
    er2->ErrorMsg = "ErrMsg222";
    req.errorinfo->Errors.append(er);
    req.errorinfo->Errors.append(er2);

    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    ReqStructTaskExecStatus req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }

    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test RespStructFilesDownloadStatus
#include <QCoreApplication>
#include <QtCore>
#include "respstructfilesdownloadstatus.h"

int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    RespStructFilesDownloadStatus req;

    req.MessageType = 0xC;
    req.UUID = 15101010;
    req.RequestID = 0x1;
    req.TaskUUID = 0x12345678;
    req.State = 98;

    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    RespStructFilesDownloadStatus req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }

    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test ReqStructFilesDownloadStatus
#include <QCoreApplication>
#include <QtCore>
#include "reqstructfilesdownloadstatus.h"

int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    ReqStructFilesDownloadStatus req;

    req.MessageType = 0xB;
    req.UUID = 15101010;
    req.RequestID = 0x1;
    req.TaskUUID = 0x12345678;
    req.State = 98;
    req.Strategy = 666;

    Error *er = new Error;
    er->DownloadURLs = "ftp://ip:port/project/111.txt";
    er->ErrorMsg = "ErrMsg111";
    Error *er2 = new Error;
    er2->DownloadURLs = "ftp://ip:port/project/222.txt";
    er2->ErrorMsg = "ErrMsg222";
    req.errorinfo->Errors.append(er);
    req.errorinfo->Errors.append(er2);

    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    ReqStructFilesDownloadStatus req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }

    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test RespStructFilesDownloadInfo
#include <QCoreApplication>
#include <QtCore>
#include "respstructfilesdownloadinfo.h"


int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    RespStructFilesDownloadInfo req;

    req.MessageType = 0xA;
    req.UUID = 15101010;
    req.RequestID = 0x1;
    req.TaskUUID = 0x12345678;
    req.State =  89;

    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    RespStructFilesDownloadInfo req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }

    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test ReqStructFilesDownloadInfo
#include <QCoreApplication>
#include <QtCore>
#include "reqstructfilesdownloadinfo.h"

int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    ReqStructFilesDownloadInfo req;

    req.MessageType = 0x9;
    req.UUID = 15101010;
    req.RequestID = 0x1;
    req.TaskUUID = 0x12345678;
    req.TaskExecType = 99;
    req.Strategy = 555;
    req.setExecTime("20150813161015");

    FileDownload *fd = new FileDownload;
    fd->DownloadURLs = "ftp://ip:port/project/111.txt";
    fd->DescPath = "d:/111.txt";
    FileDownload *fd2 = new FileDownload;
    fd2->DownloadURLs = "ftp://ip:port/project/222.txt";
    fd2->DescPath = "d:/222.txt";
    req.ftpPush->IP = "127.0.0.1";
    req.ftpPush->Port = 21;
    req.ftpPush->Username = "user01";
    req.ftpPush->Password = "pwd01";
    req.ftpPush->FilesDownloadURLs.append(fd);
    req.ftpPush->FilesDownloadURLs.append(fd2);

    FileDownload *fd3 = new FileDownload;
    fd3->DownloadURLs = "http://ip:port/project/111.txt";
    fd3->DescPath = "d:/111.txt";
    FileDownload *fd4 = new FileDownload;
    fd4->DownloadURLs = "http://ip:port/project/222.txt";
    fd4->DescPath = "d:/222.txt";
    req.httpPush->FilesDownloadURLs.append(fd3);
    req.httpPush->FilesDownloadURLs.append(fd4);

    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    ReqStructFilesDownloadInfo req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }

    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test RespUnstructFilesDownloadStatus
#include <QCoreApplication>
#include <QtCore>
#include "respunstructfilesdownloadstatus.h"

int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    RespUnstructFilesDownloadStatus req;

    req.MessageType = 0x8;
    req.UUID = 15101010;
    req.RequestID = 0x1;
    req.TaskUUID = 0x12345678;
    req.State = 66;

    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    RespUnstructFilesDownloadStatus req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }

    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test ReqUnstructFilesDownloadStatus
#include <QCoreApplication>
#include <QtCore>
#include "requnstructfilesdownloadstatus.h"

int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    ReqUnstructFilesDownloadStatus req;

    req.MessageType = 0x7;
    req.UUID = 15101010;
    req.RequestID = 0x1;
    req.TaskUUID = 0x12345678;
    req.State = 66;
    req.Strategy = 123;
    Error *er = new Error;
    er->DownloadURLs = "ftp://ip:port/project/111.txt";
    er->ErrorMsg = "ErrMsg111";
    Error *er2 = new Error;
    er2->DownloadURLs = "ftp://ip:port/project/222.txt";
    er2->ErrorMsg = "ErrMsg222";
    req.errorinfo->Errors.append(er);
    req.errorinfo->Errors.append(er2);

    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    ReqUnstructFilesDownloadStatus req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }

    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test RespUnstructFilesDownloadInfo
#include <QCoreApplication>
#include <QtCore>
#include "respunstructfilesdownloadinfo.h"

int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    RespUnstructFilesDownloadInfo req;

    req.MessageType = 0x6;
    req.UUID = 15101010;
    req.RequestID = 0x1;
    req.State = 66;
    req.TaskUUID = 0x12345678;

    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    RespUnstructFilesDownloadInfo req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }

    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test RespHeartthrobsConn
#include <QCoreApplication>
#include <QtCore>
#include "respheartthrobsconn.h"

int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    RespHeartthrobsConn req;

    req.MessageType = 0x4;
    req.UUID = 15101010;
    req.RequestID = 0x1;
    req.State = 66;


    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    RespHeartthrobsConn req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test ReqHeartthrobsConn
#include <QCoreApplication>
#include <QtCore>
#include "reqheartthrobsconn.h"

int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    ReqHeartthrobsConn req;

    req.MessageType = 0x3;
    req.UUID = 15101010;
    req.RequestID = 0x1;


    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    ReqHeartthrobsConn req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test RespBridgeConn
#include <QCoreApplication>
#include <QtCore>
#include "respbridgeconn.h"

int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    RespBridgeConn req;

    req.MessageType = 0x2;
    req.UUID = 15101010;
    req.RequestID = 0x1;
    req.State = 55;
    req.PubKey = 0x12345678;

    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    RespBridgeConn req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    return app.exec();
}
*/
/*
//////////////////////////////////////////////////////////////////test ReqBridgeConn
#include <QCoreApplication>
#include <QtCore>
#include "reqbridgeconn.h"
int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    //生成报文
    ReqBridgeConn req;

    req.MessageType = 0x1;
    req.UUID = 15101010;
    req.RequestID = 0x1;
    req.PubKey = 0x12345678;

    QString message;
    QXmlStreamWriter writer(&message);
    try
    {
        req.toXML(&writer);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    qDebug() << message;
    //报文生实体
    ReqBridgeConn req2;
    QXmlStreamReader reader(message);
    try
    {
        req2.toEntity(&reader);
    }
    catch(TransException &excep)
    {
       qDebug() << excep.getText();
       return 0;
    }
    return app.exec();
}
*/
