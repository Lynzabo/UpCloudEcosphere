#include "lssendstatusrunnable.h"
#include "avro.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendstatus.h"
#include "../../UpCloud-Service-Center/FrontBusinessIServer/DDMIServer/StructOperaIServer/util/structutil.h"
using namespace Environment::Datagram::UI_Ctrl::Opera_Type;
using namespace Environment::Duplex_Interaction;
using QtJson::JsonArray;
using QtJson::JsonObject;
using namespace RemoteUIEnvironment;

ListStructSendStatusRunnable::ListStructSendStatusRunnable(QObject *object):m_object(object)
{
    m_cbMsg.clear();
    m_cbMsgId = 0;
    qRegisterMetaType<CsRStructSendStatus>("CsRStructSendStatus");
    qRegisterMetaType<QList<CsRStructSendStatus> >("QList<CsRStructSendStatus>");
}

void ListStructSendStatusRunnable::run()
{
    bool ok;
    quint8 rState;
    QString result;result.clear();
    QList<CsRStructSendStatus> statusList;
    QStringList nameList;
    JsonObject json;
    JsonObject jsonObj;
    JsonObject resultObj;resultObj.clear();
    JsonObject paramsObj;paramsObj.clear();
    QString pageStr;pageStr.clear();
    QString resultStr;resultStr.clear();
    QString paramsStr;paramsStr.clear();
    QString statusStr;statusStr.clear();
    QString resultNameList;resultNameList.clear();
    json.insert("taskUuid",m_taskUuid);
    //禁止同时传参节点服务器 和 文件名
    if(!m_clientUuid.isEmpty() && !m_fileName.isEmpty()) {
        return;
    }
    if(!m_clientUuid.isEmpty()) {
        json.insert("clientUuid",m_clientUuid);
    }
    else {
        json.insert("fileName",m_fileName);
    }

    paramsStr = QtJson::serialize(json);
    jsonObj.insert("paramsObj",paramsStr);
    if(!m_page->isEmpty()) {
        m_page->setResults({});
        PageUtil::pageEntityTojsonStr(*m_page,"",pageStr);
    }
    jsonObj.insert("pageStr",pageStr);
    QString params = QtJson::serialize(jsonObj);
    //准备消息发送端
    DPSender* sender = UpCloudDuplexFactory::getInstance().createDPSender();
    if(!sender) {
        qDebug() << trs("消息发送端 错误");
        return;
    }
    //准备数据
    sender->setExecType(Control_Module::Struct_listStatus);
    sender->setParams(params);

    //准备结果集
    DPResult* resultSet = sender->doSendBySync();
    rState = resultSet->getRState();
    result = resultSet->getRContent();
    //通用效验
    //地址无效
    if(rState == Data_Authority::_2) {
        qDebug() << Data_Authority::_2_DESC_AddrIsInvalid;
        m_cbMsgId = CallbackStatus::Unstruct::_1;
        m_cbMsg = CallbackStatus::Unstruct::_1_Desc_AddrIsInvalid;
    }
    //未授权访问
    else if(rState == Data_Authority::_1) {
        qDebug() << Data_Authority::_1_DESC_Unauthorized;
        m_cbMsgId = CallbackStatus::Unstruct::_2;
        m_cbMsg = CallbackStatus::Unstruct::_2_Desc_Unauthorized;
    }
    //数据库操作失败
    else if(rState == Data_Authority::_4) {
        qDebug() << Data_Authority::_4_DESC_DatabaseError;
        m_cbMsgId = CallbackStatus::Unstruct::_3;
        m_cbMsg = CallbackStatus::Unstruct::_3_Desc_DatabaseError;
    }
    //解析参数失败
    else if(rState == Data_Authority::_5) {
        qDebug() << Data_Authority::_5_DESC_ParamParseError;
        m_cbMsgId = CallbackStatus::Unstruct::_4;
        m_cbMsg = CallbackStatus::Unstruct::_4_Desc_ParamParseError;
    }
    //没有可下发的节点服务器
    else if(rState == Data_Authority::_6) {
        qDebug() << Data_Authority::_6_DESC_NoderIsNull;
        m_cbMsgId = CallbackStatus::Unstruct::_5;
        m_cbMsg = CallbackStatus::Unstruct::_5_Desc_SeiviceIsNull;
    }
    //解析返回数据失败
    else if(rState == Data_Authority::_8) {
        qDebug() << Data_Authority::_8_DESC_ParseDataError;
        m_cbMsgId = CallbackStatus::Unstruct::_6;
        m_cbMsg = CallbackStatus::Unstruct::_6_Desc_ParseDataError;
    }
    //自定义校验 服务端获取参数为空
    else if(rState == Data_Authority::_7) {
        qDebug() << Data_Authority::_7_DESC_ParamsHasNullValue;
        m_cbMsgId = CallbackStatus::Unstruct::_7;
        m_cbMsg = CallbackStatus::Unstruct::_7_Desc_ParamsHasNullValue;
    }
    //操作成功
    //TODO 需要解析结果集
    else if(rState == Data_Authority::_0 ) {
        jsonObj = QtJson::parse(result,ok).toMap();
        if(!ok) {
            goto paramsError;
        }
         paramsStr = jsonObj.value("paramsObj").toString();
        paramsObj = QtJson::parse(paramsStr,ok).toMap();
        if(!ok) {
            goto paramsError;
        }
        //解析查询参数

        /*
        if(!m_clientUuid.isEmpty()) {
            m_clientUuid = paramsObj.value("clientUuid").toString();
        }
        else {
            m_fileName = paramsObj.value("fileName").toString();
        }
         */

        //        m_taskUuid = paramsObj.value("resultStr").toString();
        pageStr = jsonObj.value("pageStr").toString();
        ok = PageUtil::pageEntityFromjsonStr(pageStr,*this->m_page,resultStr);
        if(!ok) {
            goto paramsError;
        }
        resultObj = QtJson::parse(resultStr).toMap();
        if(!ok) {
            goto paramsError;
        }
        resultNameList = resultObj.value("nameList").toString();
        nameList = QtJson::parse(resultNameList,ok).toStringList();
        if(!ok) {
            goto paramsError;
        }
        statusStr = resultObj.value("statusStr").toString();
        ok = StructUtil::taskSendStatusEntityFromjsonStr(statusList,statusStr);
        if (!ok)
        {
paramsError:
            m_cbMsgId = CallbackStatus::Unstruct::_4;
            m_cbMsg = CallbackStatus::Unstruct::_4_Desc_ParamParseError;
        }
        else {
            m_cbMsgId = CallbackStatus::Unstruct::_0;
        }

    }else{}
    if(m_fileName.isEmpty()) {
        QMetaObject::invokeMethod(m_object,"on_itemtaskCallbackNode",Qt::QueuedConnection,
                                  Q_ARG(qint32,m_cbMsgId),
                                  Q_ARG(QString,m_cbMsg),
                                  Q_ARG(QList<CsRStructSendStatus>,statusList),
                                  Q_ARG(QStringList,nameList)
                                  );
    }
    else {
        QMetaObject::invokeMethod(m_object,"on_itemtaskCallbackFile",Qt::QueuedConnection,
                                  Q_ARG(qint32,m_cbMsgId),
                                  Q_ARG(QString,m_cbMsg),
                                  Q_ARG(QList<CsRStructSendStatus>,statusList),
                                  Q_ARG(QStringList,nameList)
                                  );


    }

    sender->destory();
}

void ListStructSendStatusRunnable::setNodeUuid(const QString &taskUuid, const QString &clientUuid)
{
    m_taskUuid = taskUuid;
    m_clientUuid = clientUuid;
}

void ListStructSendStatusRunnable::setFileName(const QString &taskUuid, const QString &fileName)
{
    m_taskUuid = taskUuid;
    m_fileName = fileName;
}

void ListStructSendStatusRunnable::setFilterPage(Page *page)
{
    m_page = page;
}

