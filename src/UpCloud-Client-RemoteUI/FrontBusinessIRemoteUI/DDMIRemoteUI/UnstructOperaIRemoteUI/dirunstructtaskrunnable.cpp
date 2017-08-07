#include "dirunstructtaskrunnable.h"
#include "util/pageutil.h"
#include "../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrutask.h"
#include "../../../../UpCloud-Service-Center/FrontBusinessIServer/DDMIServer/UnstructOperaIServer/util/unstructutil.h"
using namespace Environment::Datagram::UI_Ctrl::Opera_Type;
using QtJson::JsonObject;
using QtJson::JsonArray;
using namespace Environment::Duplex_Interaction;
using namespace RemoteUIEnvironment;
DirUnstructTaskRunnable::DirUnstructTaskRunnable(QObject *object):m_object(object)
{
    cbMsg.clear();
    cbMsgId = 0;
    qRegisterMetaType<CsRUnstructTask>("CsRUnstructTask");
    qRegisterMetaType<QList<CsRUnstructTask> >("QList<CsRUnstructTask>");
}

void DirUnstructTaskRunnable::run()
{
    QList<CsRUnstructTask> taskList;
    QVariantMap requestParamsObj;requestParamsObj.clear();
    //返回结果集
    QString resultStr;resultStr.clear();
    bool ok;
    QString paramsStr = QtJson::serialize(m_map);
    QString pageStr;
    if(!m_page->isEmpty())
    {
        m_page->setResults({});
        PageUtil::pageEntityTojsonStr(*m_page,QString(""),pageStr);
    }
    requestParamsObj["paramsStr"] = paramsStr;
    requestParamsObj["pageStr"] = pageStr;
    QString params = QtJson::serialize(requestParamsObj);

    //1.准备消息发送端
    DPSender* sender = UpCloudDuplexFactory::getInstance().createDPSender();
    if(!sender) {
        return;
    }
    //2.请求数据
    sender->setExecType(Control_Module::Unstruct_listTask);
    sender->setParams(params);
    //3.准备结果集
    DPResult* resultSet = sender->doSendBySync();
    if(!resultSet) {
        return;
    }
    quint8 rState = resultSet->getRState();
    QString result = resultSet->getRContent();
    //通用校验
    //地址无效
    if(rState == Data_Authority::_2) {
        qDebug() << Data_Authority::_2_DESC_AddrIsInvalid;
        cbMsgId = CallbackStatus::Unstruct::_1;
        cbMsg = CallbackStatus::Unstruct::_1_Desc_AddrIsInvalid;
    }
    //未授权访问
    else if(rState == Data_Authority::_1) {
        qDebug() << Data_Authority::_1_DESC_Unauthorized;
        cbMsgId = CallbackStatus::Unstruct::_2;
        cbMsg = CallbackStatus::Unstruct::_2_Desc_Unauthorized;
    }
    //数据库操作失败
    else if(rState == Data_Authority::_4) {
        qDebug() << Data_Authority::_4_DESC_DatabaseError;
        cbMsgId = CallbackStatus::Unstruct::_3;
        cbMsg = CallbackStatus::Unstruct::_3_Desc_DatabaseError;
    }
    //解析参数失败
    else if(rState == Data_Authority::_5) {
        qDebug() << Data_Authority::_5_DESC_ParamParseError;
        cbMsgId = CallbackStatus::Unstruct::_4;
        cbMsg = CallbackStatus::Unstruct::_4_Desc_ParamParseError;
    }
    //没有可下发的节点服务器
    else if(rState == Data_Authority::_6) {
        qDebug() << Data_Authority::_6_DESC_NoderIsNull;
        cbMsgId = CallbackStatus::Unstruct::_5;
        cbMsg = CallbackStatus::Unstruct::_5_Desc_SeiviceIsNull;
    }
    //解析返回数据失败
    else if(rState == Data_Authority::_8) {
        qDebug() << Data_Authority::_8_DESC_ParseDataError;
        cbMsgId = CallbackStatus::Unstruct::_6;
        cbMsg = CallbackStatus::Unstruct::_6_Desc_ParseDataError;
    }
    //自定义校验 服务端获取参数为空
    else if(rState == Data_Authority::_7) {
        qDebug() << Data_Authority::_7_DESC_ParamsHasNullValue;
        cbMsgId = CallbackStatus::Unstruct::_7;
        cbMsg = CallbackStatus::Unstruct::_7_Desc_ParamsHasNullValue;
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
        ok = PageUtil::pageEntityFromjsonStr(pageStr,*(this->m_page),resultStr);
        if(!ok)
        {
            goto paramsError;
        }
        ok = UnstructUtil::taskEntityFromjsonStr(taskList,resultStr);
        if (!ok)
        {
            paramsError:
            qDebug("解析返回数据失败");
            cbMsgId = CallbackStatus::Unstruct::_6;
            cbMsg = CallbackStatus::Unstruct::_6_Desc_ParseDataError;
        }
        {
            cbMsgId = CallbackStatus::Unstruct::_0;

        }
    }else{}
    QMetaObject::invokeMethod(m_object,"on_itemtaskCallback",Qt::QueuedConnection,
                              Q_ARG(qint32,cbMsgId),
                              Q_ARG(QString,cbMsg),
                              Q_ARG(QList<CsRUnstructTask>,taskList)
                              );
    sender->destory();
}

void DirUnstructTaskRunnable::setListCondition(const QVariantMap &map)
{
    m_map = map;
}

void DirUnstructTaskRunnable::setFilterPage(Page *_page)
{
    m_page = _page;
}

