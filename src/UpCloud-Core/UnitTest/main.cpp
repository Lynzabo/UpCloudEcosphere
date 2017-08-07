/*
//测试串口通讯代码
#include <QCoreApplication>
#include "base.h"
#include "serialpool.h"
#include "serial/core/serialdatagramutil.h"
#include <QTimer>

using namespace Environment::Serial;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    static SerialPool scheduler;
    scheduler.connectCom();
    QTimer timer1;
    timer1.start(3000);


    QByteArray datagram;
    SerialDatagramUtil::packDatagram(DataType::GPS, datagram);


    QObject::connect(&scheduler, SIGNAL(evt_disconnectCom()), &a, SLOT(quit()), Qt::QueuedConnection);
    QObject::connect(&timer1, &QTimer::timeout, [=] () {scheduler.write(datagram);});

    //    static SerialPool scheduler1;
    //    scheduler1.connectCom();
    //    QTimer timer1;
    //    timer1.start(1000);
    //    QObject::connect(&scheduler1, SIGNAL(evt_disconnectCom()), &a, SLOT(quit()), Qt::QueuedConnection);
    //    QObject::connect(&timer1, &QTimer::timeout, [=] () {scheduler1.write("2");});

    return a.exec();
}
*/
//test db page
#include <QCoreApplication>
#include <QtCore>
#include "db.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString confPath = QString(trs("C:/UpCloud-package/conf/NodeServer-db.conf"));
    DatabaseConnectionPool::initialize(confPath);

    DatabaseMeta::Builder *builder = new DatabaseMeta::Builder;
    DatabaseMeta *dbMeta = builder->setDbName(DatabaseMeta::DbName::MYSQL)
            ->setIp(trs("10.0.0.110"))->setPort(3306)->setInstanceName(trs("test"))
            ->setUsername(trs("root"))->setPassword(trs("root"))->build();

    Page* page = new Page;
    //设置第几页
    page->setCurPageNum((quint32)1);
    //设置每页显示条数
    page->setNumPerPage((quint32)20);
    //设置排序字段
    page->setOrderFieldName(trs("age"));
    //设置排序方式
    page->setOrderField(Qt::SortOrder::DescendingOrder);
    QString sql;
    QVariantMap params;

    sql = "select * from people where 1 = 1";
    QString odfName = page->getOrderFieldName();
    if(!(odfName.isEmpty()))
    {
        if(odfName == trs("name"))
        {
            sql.append(trs(" order by name"));
        }
        else if(odfName == trs("age"))
        {
            sql.append(trs(" order by age"));
        }
        sql.append((page->getOrderField() == Qt::SortOrder::DescendingOrder) ? trs(" desc"):trs(" asc"));
    }
    DBQuery query;
    query.setDatabaseMeta(*dbMeta);
    try
    {
        page = query.page(page,sql,params);
        qDebug() << "Page OK!";
        quint32 curPageNum;
        //每页显示条数
        quint32 numPerPage;
        //倒序还是正序
        // Order orderField;
        //排序字段名
        QString orderFieldName;
        //总页数
        quint32 totalPages;
        //所有记录总条数
        quint64 totalCount;
        //记录
        QList<QVariantMap> results;
        qDebug() << "curPageNum = " << page->getCurPageNum();
        qDebug() << "numPerPage = " << page->getNumPerPage();
        qDebug() << "orderFieldName = " << page->getOrderFieldName();
        qDebug() << "totalPages = " << page->getTotalPages();
        qDebug() << "totalCount = " << page->getTotalCount();
        for(int i=0; i<page->getResults().size(); i++)
        {
            qDebug() << "result:" << page->getResults().at(i);
        }
        qDebug("Test End!");
    }
    catch(DBException &ex)
    {
        qDebug() << trs("Exec Error");
    }
    DatabaseConnectionPool::release();
    return a.exec();
}
/*
//test ftpcommonmanager

#include <QCoreApplication>
#include <QtCore>
#include "base.h"
#include "ftp/ftpcommonmanager.h"
int main(int argc, char *argv[])
{
    QCoreApplication app( argc, argv );

    FtpCommonManager ftpcom;
    FtpMeta::Builder* builder = new FtpMeta::Builder;
    FtpMeta *m_meta = (FtpMeta *)builder->setHostname("10.0.0.110")
            ->setPort(21)
            ->setUsername("ftp_u1")
            ->setPassword("ftp_u1")->build();
    ftpcom.init(m_meta);

    qint64 size;
    ftpcom.size("test6.txt", &size);
    return app.exec();
}
*/

/*
#include <QCoreApplication>
#include <QtCore>
#include "db.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
<<<<<<< .mine
    QString confPath = QString(trs("C:/UpCloud-package/conf/NodeServer-db.conf"));
    DatabaseConnectionPool::initialize(confPath);
    /*bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString tasksql = "insert into NS_R_UNSTRUCT_TASK(UUID, TASK_NUM, STRATEGY, STATE, INSERT_TIME) values (:uuid, :taskNum, :strategy, :state, :insertTime)";

    QVariantMap taskparams;
    taskparams["uuid"] = QString("dsdasdasfdsfsdddas");
    taskparams["taskNum"] = 1;
    taskparams["strategy"] = 1;
    taskparams["state"]    = QChar('0');
    taskparams["insertTime"]   = QString("dsdasdasdas");
    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        fly = transaction->execSQL(tasksql,taskparams);
        if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
        {
            transaction->commit();
        }
        else
        {
            error:;
            transaction->rollback();
            DBException excep;
            excep.setType(QSqlError::TransactionError);
            excep.setText(trs("insert error"));
            throw excep;
        }
    }
    catch(DBException &ex)
    {
        qDebug() << trs("插入失败:%1").arg(ex.getText());
        transaction->rollback();
        //        qDebug() << excep.getText();
        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
        throw ex;
    }
    QString sql = "select TASK_NUM from ns_r_unstruct_task WHERE UUID =:taskUUID";
    QVariantMap params;
    params["taskUUID"]       = QString("dsdasdasfdsfsdddas");
    DBQuery query;
    int taskNum = (quint32)query.selectVariant(sql, params).toUInt();

    QString sql2 = "select TASK_NUM from ns_r_unstruct_task WHERE UUID =:taskUUID";
    QVariantMap params2;
    params2["taskUUID"]       = QString("111");
    DBQuery query2;
    DatabaseMeta::Builder *builder = new DatabaseMeta::Builder;
    DatabaseMeta *dbMeta = builder->setDbName(DatabaseMeta::DbName::MYSQL)->setIp(trs("10.0.0.114"))->setPort(3306)->setInstanceName(trs("c##nodeserver"))
            ->setUsername(trs("root"))->setPassword(trs("root"))->build();
    query2.setDatabaseMeta(*dbMeta);
    int taskNum2 = (quint32)query2.selectVariant(sql2, params2).toUInt();
    DatabaseConnectionPool::release();
    ////1.Ftp同步下载单通道测试

    FtpMeta::Builder *builder = new FtpMeta::Builder;
    FtpMeta *meta = (FtpMeta *)builder->setHostname(QString("10.0.0.111"))
            ->setPort(21)
            ->setUsername(QString("dudu"))
            ->setPassword(QString("dudu"))->build();
    NetTransClient *ftpClient = new FTPClientPool(meta);
    QMap<QString, QString> downGroups;
    downGroups.clear();
    downGroups.insert(QString("test4.txt"),QString("d:/test/test4.txt"));
    downGroups.insert(QString("test6.txt"),QString("d:/test/test6.txt"));
    ftpClient->download(downGroups,true,true);
    delete ftpClient;
    return a.exec();
}


//#include <QCoreApplication>
//#include <QtCore>
//#include "db.h"
//#include "base.h"
//#include "net.h"
//#include "ftptool.h"
//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);
//    FtpTool *tool = new FtpTool;
//    tool->download();
//    ////1.Ftp同步下载单通道测试
//    /*
//    FtpMeta::Builder *builder = new FtpMeta::Builder;
//    FtpMeta *meta = (FtpMeta *)builder->setHostname(QString("10.0.0.111"))
//            ->setPort(21)
//            ->setUsername(QString("dudu"))
//            ->setPassword(QString("dudu"))->build();
//    NetTransClient *ftpClient = new FTPClientPool(meta);
//    QMap<QString, QString> downGroups;
//    downGroups.clear();
//    downGroups.insert(QString("test4.txt"),QString("d:/test/test4.txt"));
//    downGroups.insert(QString("test6.txt"),QString("d:/test/test6.txt"));
//    ftpClient->download(downGroups,true,true);
//    delete ftpClient;*/
//    return a.exec();
//}

/*
#include <QCoreApplication>
#include <QtCore>
#include "db.h"
#include "base.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString confPath = QString(trs("%1/%2")).arg(AbstPath::confAbst()).arg(trs("NodeServer-db.conf"));
    ConnectionPool::initialize(confPath);
    bool fly = Environment::Db_Transaction_State::TRANS_FAIL;
    QString tasksql = "insert into NS_R_UNSTRUCT_TASK(UUID, TASK_NUM, STRATEGY, STATE, INSERT_TIME) values (:uuid, :taskNum, :strategy, :state, :insertTime)";

    QVariantMap taskparams;
    taskparams["uuid"] = QString("dsdasdasdas");
    taskparams["taskNum"] = 1;
    taskparams["strategy"] = 1;
    taskparams["state"]    = QChar('0');
    taskparams["insertTime"]   = QString("dsdasdasdas");
    DBTransaction *transaction = new DBTransaction;
    try
    {
        transaction->beginTransaction();
        fly = transaction->execSQL(tasksql,taskparams);
        if(fly == Environment::Db_Transaction_State::TRANS_SUCCESS)
        {
            transaction->commit();
        }
        else
        {
            error:;
            transaction->rollback();
            DBException excep;
            excep.setType(QSqlError::TransactionError);
            excep.setText(trs("insert error"));
            throw excep;
        }
    }
    catch(DBException &ex)
    {
        qDebug() << trs("插入失败");
        transaction->rollback();
        //        qDebug() << excep.getText();
        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
        throw ex;
    }
    ConnectionPool::release();
    return a.exec();
}*/
/*#include <QCoreApplication>
#include <QtCore>
#include "db.h"
#include "test/unstruct/dao/csunstructdao.h"
#include "test/unstruct/bean/csrutask.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString confPath = QString(trs("%1/%2")).arg(AbstPath::confAbst()).arg(trs("CenterServer-db.conf"));
    ConnectionPool::initialize(confPath);
    try
    {
        QList<CsRUnstructTask> list = CSUnstructDao::listRTaskByStatus(1,"2015-09-25 10:40:00");
        for(CsRUnstructTask task : list)
        {
            qDebug() << task.getUuid();
        }
    }catch(DBException &excep)
    {
        qDebug() << excep.getText();
    }
    //释放数据库连接
    ConnectionPool::release();
    return a.exec();
}
*/

//////////////////////////////////////////////////////////////////测试报文装帧和解帧
//#include <QCoreApplication>
//#include <QtCore>
//#include "db.h"
////(1).最简单操作
//void foo() {
//    try
//    {
//        // 1. 从数据库连接池里取得连接
//        QSqlDatabase db = ConnectionPool::openConnection();
//        // 2. 使用连接查询数据库
//        QSqlQuery query(db);
//        query.exec("SELECT * FROM user where id=1");
//        query.exec();
//        while (query.next()) {
//            qDebug() << query.value("username").toString();
//        }
//        // 3. 连接使用完后需要释放回数据库连接池
//        ConnectionPool::closeConnection(db);
//    }
//    catch(DBException &excep)
//    {
//        //        qDebug() << excep.getText();
//        //既然try...catch,就捕获异常做处理,如果不try...catch,自动回退直到找到try...catch
//        throw excep;
//    }
//}
//int main(int argc, char *argv[]) {
//    foo();
//    ConnectionPool::release(); // 4. 释放数据库连接
//    return 0;
//}
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
//    Logger::registerSystemLogger();

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
#include <QCoreApplication>
#include <QtCore>
#include "base.h"
#include "test/user/dao/userdao.h"
#include "test/user/bean/user.h"
#include "db.h"
int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );
    try
    {
        User user = UserDao::findByUserId(1);
        qDebug() << user.username;
    }
    catch(DBException &excep)
    {
        qDebug() << "Error: type:" << excep.getType() << ",typeDesc:" << excep.getTypeDesc() << ",text:" << excep.getText();
    }
    ///////////////////////////查询操作测试//////////////////////////////////////////////////////////////
    /*
    //findByUserId
    */
/*
    //list
    try
    {
        QList<User> list = UserDao::list();
        for(User user:list)
            qDebug() << user.username;
    }
    catch(DBException &excep)
    {
        qDebug() << "Error: type:" << excep.getType() << ",typeDesc:" << excep.getTypeDesc() << ",text:" << excep.getText();
    }
    */
/*
    //listByCond
    try
    {
        QList<User> list = UserDao::listByCond(QString("%os%"));
        for(User user:list)
            qDebug() << user.username;
    }
    catch(DBException &excep)
    {
        qDebug() << "Error: type:" << excep.getType() << ",typeDesc:" << excep.getTypeDesc() << ",text:" << excep.getText();
    }
    */
/*
    //listColsByCond
    try
    {
        UserDao::listColsByCond(QString("%os%"));
    }
    catch(DBException &excep)
    {
        qDebug() << "Error: type:" << excep.getType() << ",typeDesc:" << excep.getTypeDesc() << ",text:" << excep.getText();
    }
    try
    {
        UserDao::other();
    }
    catch(DBException &excep)
    {
        qDebug() << "Error: type:" << excep.getType() << ",typeDesc:" << excep.getTypeDesc() << ",text:" << excep.getText();
    }
    */
///////////////////////////事务操作测试//////////////////////////////////////////////////////////////
/*
    //insert
    User *user = new User;
    user->id = 4;
    user->username = "Tom";
    user->email = "tom@163.com";
    user->mobile = "23131312";
    user->password = "sascs";
    try
    {
        UserDao::insert(*user);
    }
    catch(DBException &excep)
    {
        qDebug() << "Error: type:" << excep.getType() << ",typeDesc:" << excep.getTypeDesc() << ",text:" << excep.getText();
    }
    delete user;
    */
/*
    //update
    User *user = new User;
    user->id = 4;
    user->username = "Tom";
    user->email = "tom@163.com";
    user->mobile = "01010101";
    user->password = "sascs";
    try
    {
        UserDao::update(*user);
    }
    catch(DBException &excep)
    {
        qDebug() << "Error: type:" << excep.getType() << ",typeDesc:" << excep.getTypeDesc() << ",text:" << excep.getText();
    }
    delete user;
    */
/*
    //deleteRecord
    try
    {
        UserDao::deleteRecord();
    }
    catch(DBException &excep)
    {
        qDebug() << "Error: type:" << excep.getType() << ",typeDesc:" << excep.getTypeDesc() << ",text:" << excep.getText();
    }
    */
/*
    //execSQL
    try
    {
        UserDao::execSQL();
    }
    catch(DBException &excep)
    {
        qDebug() << "Error: type:" << excep.getType() << ",typeDesc:" << excep.getTypeDesc() << ",text:" << excep.getText();
    }
    */
// ConnectionPool::release();
//return app.exec();

//}
/*
#include <QCoreApplication>
#include <QtCore>
#include "base.h"
#include "db/conf/databaseconf.h"
int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );
    qDebug() << "dbDriver:" << DatabaseConf::getInstance().dbDriver();
    qDebug() << "dbName:" << DatabaseConf::getInstance().dbName();
    qDebug() << "houseKeepingSleepTime:" << DatabaseConf::getInstance().houseKeepingSleepTime();
    qDebug() << "instanceName:" << DatabaseConf::getInstance().instanceName();
    qDebug() << "ip:" << DatabaseConf::getInstance().ip();
    qDebug() << "isDebug:" << DatabaseConf::getInstance().isDebug();
    qDebug() << "maximumConnectionCount:" << DatabaseConf::getInstance().maximumConnectionCount();
    qDebug() << "minimumConnectionCount:" << DatabaseConf::getInstance().minimumConnectionCount();
    qDebug() << "password:" << DatabaseConf::getInstance().password();
    qDebug() << "port:" << DatabaseConf::getInstance().port();
    qDebug() << "testOnBorrow:" << DatabaseConf::getInstance().testOnBorrow();
    qDebug() << "testOnBorrowSql:" << DatabaseConf::getInstance().testOnBorrowSql();
    qDebug() << "username:" << DatabaseConf::getInstance().username();
    qDebug() << "waitIntervalTime:" << DatabaseConf::getInstance().waitIntervalTime();
    return app.exec();
}
*/
//#include <QCoreApplication>
//#include <QtCore>
//#include "base.h"
//int main(int argc, char *argv[])
//{
//    //注册系统日志自定义格式监听器
//    Logger::registerSystemLogger();

//    QCoreApplication app( argc, argv );
//    qDebug() << trs("说三道四");
////    qWarning() << trs("说三道A");
////    qCritical() << trs("说三道四");
//    return app.exec();
//}

//#include <QCoreApplication>
//#include <QDebug>
//#include <QtCore>
//#include "computerinfo.h"
//测试Http的异步和同步下载
//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);
//    qDebug() << ComputerInfo::getInstance()->ProcessorType();


//    ///////////////////////////////测试FTP/Http同步、异步下载---begin---
//    /*
//    ////1.Ftp同步下载单通道测试
//    FtpMeta::Builder *builder = new FtpMeta::Builder;
//    FtpMeta *meta = (FtpMeta *)builder->setHostname(QString("localhost"))
//            ->setPort(21)
//            ->setUsername(QString("user01"))
//            ->setPassword(QString("pwd01"))->build();
//    NetTransClient *ftpClient = new FTPClientPool(meta);
//    QMap<QString, QString> downGroups;
//    downGroups.clear();
//    downGroups.insert(QString("111.exe"),QString("d:/download/111.exe"));
//    downGroups.insert(QString("1111.zip"),QString("d:/download/1111.zip"));
//    ftpClient->download(downGroups,false,false);
//    delete ftpClient;
//    */
//    /*
//    ////2.Ftp同步下载多通道测试
//    FtpMeta::Builder *builder = new FtpMeta::Builder;
//    FtpMeta *meta = (FtpMeta *)builder->setHostname(QString("localhost"))
//            ->setPort(21)
//            ->setUsername(QString("user01"))
//            ->setPassword(QString("pwd01"))->build();
//    NetTransClient *ftpClient = new FTPClientPool(meta);
//    QMap<QString, QString> downGroups;
//    downGroups.clear();
//    downGroups.insert(QString("111.exe"),QString("d:/download/111.exe"));
//    downGroups.insert(QString("1111.zip"),QString("d:/download/1111.zip"));
//    ftpClient->download(downGroups,false,true);
//    delete ftpClient;
//    */
//    /*
//    ////3.Ftp异步下载单通道测试
//    FtpMeta::Builder *builder = new FtpMeta::Builder;
//    FtpMeta *meta = (FtpMeta *)builder->setHostname(QString("localhost"))
//            ->setPort(21)
//            ->setUsername(QString("user01"))
//            ->setPassword(QString("pwd01"))->build();
//    NetTransClient *ftpClient = new FTPClientPool(meta);
//    QMap<QString, QString> downGroups;
//    downGroups.clear();
//    downGroups.insert(QString("111.exe"),QString("d:/download/111.exe"));
//    downGroups.insert(QString("1111.zip"),QString("d:/download/1111.zip"));
//    ftpClient->download(downGroups,true,false);
//    qDebug() << "ayncs exec!";
//    */
//    /*
//    ////4.Ftp异步下载多通道测试
//    FtpMeta::Builder *builder = new FtpMeta::Builder;
//    FtpMeta *meta = (FtpMeta *)builder->setHostname(QString("localhost"))
//            ->setPort(21)
//            ->setUsername(QString("user01"))
//            ->setPassword(QString("pwd01"))->build();
//    NetTransClient *ftpClient = new FTPClientPool(meta);
//    QMap<QString, QString> downGroups;
//    downGroups.clear();
//    downGroups.insert(QString("111.exe"),QString("d:/download/111.exe"));
//    downGroups.insert(QString("1111.zip"),QString("d:/download/1111.zip"));
//    ftpClient->download(downGroups,true,true);
//    qDebug() << "ayncs exec!";
//    */


//    /*
//    ////1.Http同步下载单通道测试
//    NetTransClient *httpClient = new HttpCientPool;
//    QMap<QString, QString> downGroups;
//    downGroups.clear();
//    downGroups.insert(QString("http://localhost:8080/file/111.zip"),QString("d:/download/111.zip"));
//    downGroups.insert(QString("http://localhost:8080/file/222.zip"),QString("d:/download/222.zip"));
//    httpClient->download(downGroups,false,false);
//    qDebug() << "download complete exec!";
//    delete httpClient;
//    */
//    /*
//    ////2.Http同步下载多通道测试
//    NetTransClient *httpClient = new HttpCientPool;
//    QMap<QString, QString> downGroups;
//    downGroups.clear();
//    downGroups.insert(QString("http://localhost:8080/file/111.zip"),QString("d:/download/111.zip"));
//    downGroups.insert(QString("http://localhost:8080/file/222.zip"),QString("d:/download/222.zip"));
//    httpClient->download(downGroups,false,true);
//    qDebug() << "download complete exec!";
//    delete httpClient;
//    */
//    /*
//    ////3.Http异步下载单通道测试
//    NetTransClient *httpClient = new HttpCientPool;
//    QMap<QString, QString> downGroups;
//    downGroups.clear();
//    downGroups.insert(QString("http://localhost:8080/file/111.zip"),QString("d:/download/111.zip"));
//    downGroups.insert(QString("http://localhost:8080/file/222.zip"),QString("d:/download/222.zip"));
//    httpClient->download(downGroups,true,false);
//    qDebug() << "ayncs exec!";
//    */
//    /*
//    ////4.Http异步下载多通道测试
//    NetTransClient *httpClient = new HttpCientPool;
//    QMap<QString, QString> downGroups;
//    downGroups.clear();
//    downGroups.insert(QString("http://localhost:8080/file/111.zip"),QString("d:/download/111.zip"));
//    downGroups.insert(QString("http://localhost:8080/file/222.zip"),QString("d:/download/222.zip"));
//    httpClient->download(downGroups,true,true);
//    qDebug() << "ayncs exec!";
//    */
//    ///////////////////////////////测试FTP/Http同步、异步下载---end---
//    return a.exec();
//}
//#include "httpcientpool.h"
//#include "ftpclientpool.h"
/*
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    NetTransClient *httpClient = new HttpCientPool;
    QMap<QString, QString> downGroups;
    downGroups.clear();
    downGroups.insert(QString("http://localhost:8080/myeclipse-8.5.0-win32.exe"),QString("d:/myeclipse-8.5.0-win32.exe"));
    downGroups.insert(QString("http://localhost:8080/cbox.exe"),QString("d:/cbox.exe"));
    httpClient->download(downGroups,false,false);
    delete httpClient;
    return a.exec();
}*/
/*void main()
{
    QFileInfo fileInfo("d:/111/222/333.txt");
    QString directory = fileInfo.absolutePath();
    QDir dir(directory);
    if(!dir.exists())
        dir.mkpath(directory);
}*/
/*
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    HttpCientPool *httpClient = new HttpCientPool;
    httpClient->download();


    FTPClientPool::Builder *builder = new FTPClientPool::NetBuilder(
                NetManager::SERVICE::HTTP,
                QString("localhost"),
                21,
                QString("user01"),
                QString("user01"));
    FTPClientPool *net = builder->build();

    FTPClientPool::Builder *builder = new FTPClientPool::Builder;
    FTPClientPool *net = builder->setService(NetManager::SERVICE::HTTP)
            ->setHostname(QString("localhost"))
            ->setPort(21)
            ->setUsername(QString("user01"))
            ->setPassword(QString("user01"))->build();
    net->download();
    delete builder;
    FTPClientPool::Builder *builder = new FTPClientPool::Builder;
    FTPClientPool *net = (FTPClientPool *)builder->setService(FTPClientPool::SERVICE::HTTP)
            ->setHostname(QString("localhost"))
            ->setPort(21)
            ->setUsername(QString("user01"))
            ->setPassword(QString("user01"))->build();
//    net->download();
    delete builder;
    delete net;
    return a.exec();
}
*/
/*
读取conf文件测试
#include <QCoreApplication>
#include "unicode.h"
#include <QDebug>
#include <QSettings>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //qDebug() << trs("收拾ddd收拾");

    QSettings settings("E:/UpCloud/works/UpCloud-Core/BaseLib/config.conf", QSettings::IniFormat, &a);
    QString dest = settings.value("logger.dest").toString();
    QString level = settings.value("logger.level").toString();
    QString file = settings.value("logger.R.file").toString();
    qDebug() <<dest << level << file;



    return a.exec();
}*/
/*
//输出日志测试
#include <QCoreApplication>
#include <iostream>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
using namespace std;
void relMsgOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString txt;
    QByteArray localMsg = msg.toLocal8Bit();
    txt.append(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd")).append("   ");
    switch (type) {
    case QtDebugMsg:
        txt = QString("Debug   	");
        break;
    case QtWarningMsg:
        txt = QString("Warning   	");
        break;
    case QtCriticalMsg:
        txt = QString("Critical   	");
        break;
    case QtFatalMsg:
        txt = QString("Fatal   	");
        abort();
    }
    txt.append(localMsg.constData());

    QFile outFile("d:/releaselog.txt");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
}
void debMsgOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString txt;
    QByteArray localMsg = msg.toLocal8Bit();
    txt.append(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).append("   ");;
    switch (type) {
    case QtDebugMsg:
        txt = QString("Debug   	[");
        break;
    case QtWarningMsg:
        txt = QString("Warning   	[");
        break;
    case QtCriticalMsg:
        txt = QString("Critical   	[");
        break;
    case QtFatalMsg:
        txt = QString("Fatal   	[");
        abort();
    }
    txt.append(context.file).append(";");;
    txt.append(context.function).append(";");;
    txt.append(QString("%1").arg(context.line)).append("]   ");;
    txt.append(localMsg.constData());
    QFile outFile("d:/debuglog.txt");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
}
int main(int argc, char *argv[])
{
#ifdef Q_OS_WIN
#ifdef _DEBUG   //Windows环境使用VS编译器
    qInstallMessageHandler(debMsgOutput);
#else
    qInstallMessageHandler(relMsgOutput);
#endif
#else
#ifdef QT_NO_DEBUG   //非Windows环境使用mingGW编译器
    qInstallMessageHandler(relMsgOutput);
#else
    qInstallMessageHandler(debMsgOutput);
#endif
#endif
    QCoreApplication app( argc, argv );
    //以后就可以像下面这样直接打日志到文件中，而且日志也会包含时间信息
    qDebug("This is a debug message at thisisqt.com");
    qWarning("This is a warning message  at thisisqt.com");
    qCritical("This is a critical message  at thisisqt.com");
    //qFatal("This is a fatal message at thisisqt.com");
    qDebug() << __LINE__;
    return app.exec();
}

*/

/*
#include <QCoreApplication>
#include <QDebug>
#include <QSettings>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //qDebug() << trs("收拾ddd收拾");
    QSettings settings("E:/UpCloud/works/UpCloud-Core/BaseLib/config.conf", QSettings::IniFormat, &a);
    QString dest = settings.value("logger.dest").toString();
    QString level = settings.value("logger.level").toString();
    QString file = settings.value("logger.R.file").toString();
    qDebug() <<dest << level << file;



    return a.exec();
}
*/


//test ftpcommonmanager
/*
#include <QCoreApplication>
#include <QtCore>
#include "base.h"
#include "ftp/ftpcommonmanager.h"
int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );

    FtpCommonManager ftpcom;


    QList<struct list_info> listInfo;

    ftpcom.list(QString("t1"), &listInfo);


    int i=0;
    qDebug() << "@@@@@@@@@@@@@@@@@@@@@@listInfo.count()= " << listInfo.count();
    for(i; i<listInfo.count(); i++)
    {
        qDebug() <<"i=" << i << listInfo.at(i).name<<endl;
    }

   // ftpcom.mkdir("tttttt");
   // ftpcom.rmdir("tttttt");
   // ftpcom.rename("t3.txt", "t55t.txt");
    //ftpcom.remove("ggg.txt");
   // ftpcom.cd("t1");
    ftpcom.list("t1", &listInfo);
    //ftpcom.rmdir("t1");
    return app.exec();
}
*/
//#include <QCoreApplication>
//#include <QtCore>
//#include "base.h"
//#include "ftp/ftpmeta.h"
//#include "ftpclientpool.h"
//int main(int argc, char *argv[])
//{
//    //注册系统日志自定义格式监听器
//    Logger::registerSystemLogger();

//    QCoreApplication app( argc, argv );
///*
//  ////1.Ftp同步上传单通道测试
//    FtpMeta::Builder *builder = new FtpMeta::Builder;
//    FtpMeta *meta = (FtpMeta *)builder->setHostname(QString("212.212.1.118"))
//            ->setPort(21)
//            ->setUsername(QString("user01"))
//            ->setPassword(QString("user01"))->build();
//    NetTransClient *ftpClient = new FTPClientPool(meta);
//    QMap<QString, QString> upGroups;
//    upGroups.clear();
//    upGroups.insert(QString("d:/testup.txt"),QString("testup.txt"));
//    upGroups.insert(QString("d:/testup22.txt"),QString("testup22.txt"));
//    //upGroups.insert(QString("1111.zip"),QString("d:/download/1111.zip"));
//    ftpClient->upload(upGroups,false,false);
//    //delete ftpClient;


//    ////2.Ftp同步下载多通道测试
//    FtpMeta::Builder *builder = new FtpMeta::Builder;
//    FtpMeta *meta = (FtpMeta *)builder->setHostname(QString("212.212.1.118"))
//            ->setPort(21)
//            ->setUsername(QString("user01"))
//            ->setPassword(QString("user01"))->build();
//    NetTransClient *ftpClient = new FTPClientPool(meta);
//    QMap<QString, QString> upGroups;
//    upGroups.clear();
//    upGroups.insert(QString("d:/testup.txt"),QString("testup.txt"));
//    upGroups.insert(QString("d:/testup22.txt"),QString("testup22.txt"));
//    //downGroups.insert(QString("1111.zip"),QString("d:/download/1111.zip"));
//    ftpClient->upload(upGroups,false,true);
//    delete ftpClient;


//    ////3.Ftp异步下载单通道测试
//    FtpMeta::Builder *builder = new FtpMeta::Builder;
//    FtpMeta *meta = (FtpMeta *)builder->setHostname(QString("212.212.1.118"))
//            ->setPort(21)
//            ->setUsername(QString("user01"))
//            ->setPassword(QString("user01"))->build();
//    NetTransClient *ftpClient = new FTPClientPool(meta);
//    QMap<QString, QString> upGroups;
//    upGroups.clear();
//    upGroups.insert(QString("d:/testup.txt"),QString("testup.txt"));
//    upGroups.insert(QString("d:/testup22.txt"),QString("testup22.txt"));
//    ftpClient->upload(upGroups,true,false);
//    qDebug() << "ayncs exec!";

//   */
//    ////4.Ftp异步下载多通道测试
//    FtpMeta::Builder *builder = new FtpMeta::Builder;
//    FtpMeta *meta = (FtpMeta *)builder->setHostname(QString("212.212.1.118"))
//            ->setPort(21)
//            ->setUsername(QString("user01"))
//            ->setPassword(QString("user01"))->build();
//    NetTransClient *ftpClient = new FTPClientPool(meta);
//    QMap<QString, QString> upGroups;
//    upGroups.clear();
//    upGroups.insert(QString("d:/testup.txt"),QString("up/testup.txt"));
//    upGroups.insert(QString("d:/testup22.txt"),QString("up/testup22.txt"));
//    ftpClient->upload(upGroups,true,true);
//    qDebug() << "ayncs exec!";

//    return app.exec();
//}



