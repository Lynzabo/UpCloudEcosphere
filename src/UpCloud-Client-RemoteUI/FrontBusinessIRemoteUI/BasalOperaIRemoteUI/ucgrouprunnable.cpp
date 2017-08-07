#include "ucgrouprunnable.h"
#include "../../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/cscgroup.h"
#include "../../../UpCloud-Service-Center/FrontBusinessIServer/BasalOperaIServer/util/csgroupandclientutil.h"
using QtJson::JsonArray;
using QtJson::JsonObject;
using namespace Environment::Datagram::UI_Ctrl::Opera_Type;
using namespace Environment::Duplex_Interaction;
using namespace RemoteUIEnvironment;

UpdateClientGroupRunnable::UpdateClientGroupRunnable(QObject *object):m_object(object)
{
    m_cbMsg.clear();
    m_cbMsgId = 0;
    qRegisterMetaType<CsClientGroup>("CsClientGroup");
    qRegisterMetaType<QList<CsClientGroup> >("QList<CsClientGroup>");
}

void UpdateClientGroupRunnable::setGroupInfo(const QVariantMap &params)
{
    m_params = params;
}

void UpdateClientGroupRunnable::run()
{
    QString result;result.clear();
    CsClientGroup task;
    QList<CsClientGroup> taskList;taskList.clear();
    bool ok;
    quint8 rState;
    QString params;

    //准备参数列表
    task.setUuid(m_params.value("uuid").toString());
    task.setName(m_params.value("name").toString());
    task.setDescription(m_params.value("description").toString());
    task.setState((quint8)m_params.value("state").toInt());
    task.setSequence((qint32)m_params.value("sequence").toInt());
    task.setSupUuid(m_params.value("supUuid").toString());
    CsGroupAndClientUtil::taskEntinyTojsonStr(params,task);
    //准备消息发送端
    DPSender* sender = UpCloudDuplexFactory::getInstance().createDPSender();
    if(!sender) {
        qDebug() << QObject::trUtf8("准备消息发送端错误");
        return;
    }
    //准备数据
    sender->setExecType(Control_Module::Group_updClientGroup);
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
        ok = CsGroupAndClientUtil::taskEntinyFromjsonStr(taskList,result);
        if (!ok)
        {
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
                              Q_ARG(QString,m_cbMsg)
                              );

    sender->destory();
}
