#include "ldictrunnable.h"
#include "../../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/csdict.h"
#include "avro.h"
#include "../../../UpCloud-Service-Center/FrontBusinessIServer/BasalOperaIServer/util/dictutil.h"
using namespace Environment::Datagram::UI_Ctrl::Opera_Type;
using QtJson::JsonObject;
using QtJson::JsonArray;
using namespace Environment::Duplex_Interaction;
using namespace RemoteUIEnvironment;

ListDictRunnable::ListDictRunnable(QObject *object):m_object(object)
{
    m_cbMsgId = 0;
    filterFlg = true;
    m_cbMsg.clear();
    conditionMap.clear();
    qRegisterMetaType<CsDict>("CsDict");
    qRegisterMetaType<QList<CsDict> >("QList<CsDict>");
}



void ListDictRunnable::setSelectCondition(const QVariantMap &conditionMap)
{
    this->conditionMap = conditionMap;
}

void ListDictRunnable::setFilterPage(Page *page)
{
    this->page = page;
}

void ListDictRunnable::setFilterUnused()
{
    this->conditionMap["closeFilter"] = "";
    filterFlg = false;
}

void ListDictRunnable::setRecursion(bool recFlg)
{
    recursionFlg = recFlg;
    if(!recursionFlg) {
        this->conditionMap["closeRecursion"] = "";
    }
}
void ListDictRunnable::run()
{
    QList<CsDict> dictList;dictList.clear();
    bool ok;

    quint8 rState;
    QString result;result.clear();
    QString params;params.clear();
    QString paramsStr;paramsStr.clear();
    QString pageStr;pageStr.clear();
    QString resultStr;resultStr.clear();
    JsonObject paramsObj;paramsObj.clear();
    //准备参数列表

    paramsStr = QtJson::serialize(conditionMap);
    if(filterFlg) {
        //分页参数
        if(!page->isEmpty())
        {
            page->setResults({});
            PageUtil::pageEntityTojsonStr(*page,QString(""),pageStr);
        }
    }
    paramsObj["paramsStr"] = paramsStr;
    paramsObj["pageStr"] = pageStr;
    params = QtJson::serialize(paramsObj);
    //准备消息发送端
    DPSender* sender = UpCloudDuplexFactory::getInstance().createDPSender();
    if(!sender) {
        qDebug() << QObject::trUtf8("准备消息发送端 ");
        return;
    }
    //准备数据
    sender->setExecType(Control_Module::Dict_list);
    sender->setParams(params);

    //准备结果集
    DPResult* resultSet = sender->doSendBySync();
    rState = resultSet->getRState();
    result = resultSet->getRContent();
    //通用效验
    //地址无效
    if(rState == Data_Authority::_2) {
        qDebug() << Data_Authority::_2_DESC_AddrIsInvalid;
        m_cbMsgId = CallbackStatus::Basal::_1;
        m_cbMsg = CallbackStatus::Basal::_1_Desc_AddrIsInvalid;
    }
    //未授权访问
    else if(rState == Data_Authority::_1) {
        qDebug() << Data_Authority::_1_DESC_Unauthorized;
        m_cbMsgId = CallbackStatus::Basal::_2;
        m_cbMsg = CallbackStatus::Basal::_2_Desc_Unauthorized;
    }
    //数据库操作失败
    else if(rState == Data_Authority::_4) {
        qDebug() << Data_Authority::_4_DESC_DatabaseError;
        m_cbMsgId = CallbackStatus::Basal::_3;
        m_cbMsg = CallbackStatus::Basal::_3_Desc_DatabaseError;
    }
    //解析参数失败
    else if(rState == Data_Authority::_5) {
        qDebug() << Data_Authority::_5_DESC_ParamParseError;
        m_cbMsgId = CallbackStatus::Basal::_4;
        m_cbMsg = CallbackStatus::Basal::_4_Desc_ParamParseError;
    }
    //没有可下发的节点服务器
    else if(rState == Data_Authority::_6) {
        qDebug() << Data_Authority::_6_DESC_NoderIsNull;
        m_cbMsgId = CallbackStatus::Basal::_5;
        m_cbMsg = CallbackStatus::Basal::_5_Desc_SeiviceIsNull;
    }
    //解析返回数据失败
    else if(rState == Data_Authority::_8) {
        qDebug() << Data_Authority::_8_DESC_ParseDataError;
        m_cbMsgId = CallbackStatus::Basal::_6;
        m_cbMsg = CallbackStatus::Basal::_6_Desc_ParseDataError;
    }
    //自定义校验 服务端获取参数为空
    else if(rState == Data_Authority::_7) {
        qDebug() << Data_Authority::_7_DESC_ParamsHasNullValue;
        m_cbMsgId = CallbackStatus::Basal::_7;
        m_cbMsg = CallbackStatus::Basal::_7_Desc_ParamsHasNullValue;
    }
    //操作成功
    else if(rState == Data_Authority::_0) {
        paramsStr.clear();
        pageStr.clear();
        //解析参数列表
        QVariantMap resultObj = QtJson::parse(result, ok).toMap();
        if(!ok)
        {
            goto paramsError;
        }
        //获取服务器传递来查询条件列表
        /*paramsStr = resultObj["paramsStr"].toString();
        QVariantMap paramsObj = QtJson::parse(paramsStr, ok).toMap();
        if(!ok)
        {
            goto paramsError;
        }*/
        pageStr = resultObj["pageStr"].toString();
        //将分页page字符串传入page对象和代表列表结果集字符串中
        if(filterFlg) {
            ok = PageUtil::pageEntityFromjsonStr(pageStr,*(this->page),resultStr);
        }
        else {
            Page temPage;
            ok = PageUtil::pageEntityFromjsonStr(pageStr,temPage,resultStr);
        }
        if(!ok)
        {
            goto paramsError;
        }
        ok = DictUtil::taskEntinyFromjsonStr(dictList,resultStr);
        if (!ok)
        {
paramsError:
            qDebug("解析返回数据失败");
            m_cbMsgId = CallbackStatus::Basal::_6;
            m_cbMsg = CallbackStatus::Basal::_6_Desc_ParseDataError;
        }
        else {
            m_cbMsgId = CallbackStatus::Basal::_0;
        }

    }else{}
    QMetaObject::invokeMethod(m_object,"on_itemtaskCallback",Qt::QueuedConnection,
                              Q_ARG(qint32,m_cbMsgId),
                              Q_ARG(QString,m_cbMsg),
                              Q_ARG(QList<CsDict>,dictList)
                              );

    sender->destory();
}


