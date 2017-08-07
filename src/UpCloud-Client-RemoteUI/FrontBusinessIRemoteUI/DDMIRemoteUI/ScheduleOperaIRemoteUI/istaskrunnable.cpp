#include "istaskrunnable.h"
#include "../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrsctask.h"
#include "../../UpCloud-Service-Center/FrontBusinessIServer/DDMIServer/ScheduleOperaIServer/util/scheduleutil.h"
using namespace Environment::Datagram::UI_Ctrl::Opera_Type;
using QtJson::JsonArray;
using QtJson::JsonObject;
using namespace RemoteUIEnvironment;
using namespace Environment::Duplex_Interaction;
ItemScheduleTaskRunnable::ItemScheduleTaskRunnable(QObject *object):m_object(object)
{
    m_cbMsg.clear();
    m_cbMsgID = 0;
    qRegisterMetaType<CsRScheduleTask>("CsRScheduleTask");
}

void ItemScheduleTaskRunnable::setTaskUuid(const QString &taskUuid)
{
    m_taskUuid = taskUuid;
}

void ItemScheduleTaskRunnable::run()
{
    bool ok = false;
    quint8 rState;
    QString result;result.clear();
    CsRScheduleTask task;
    //准备参数 序列化
    QString params = QtJson::serialize(m_taskUuid);
    //准备消息发送端
    DPSender* sender = UpCloudDuplexFactory::getInstance().createDPSender();
    if(!sender)
    {
        qDebug() << trs("准备消息发送端失败");
        return;
    }
    sender->setExecType(Control_Module::Schedule_itemTask);
    sender->setParams(params);
    //准备结果集
    DPResult* resultSet = sender->doSendBySync();
    result = resultSet->getRContent();
    rState = resultSet->getRState();
    //地址无效
    if(rState == Data_Authority::_2) {
        qDebug() << Data_Authority::_2_DESC_AddrIsInvalid;
        m_cbMsgID = CallbackStatus::Schedule::_1;
        m_cbMsg = CallbackStatus::Schedule::_1_Desc_AddrIsInvalid;
    }
    //未授权访问
    else if(rState == Data_Authority::_1) {
        qDebug() << Data_Authority::_1_DESC_Unauthorized;
        m_cbMsgID = CallbackStatus::Schedule::_2;
        m_cbMsg = CallbackStatus::Schedule::_2_Desc_Unauthorized;
    }
    //数据库操作失败
    else if(rState == Data_Authority::_4) {
        qDebug() << Data_Authority::_4_DESC_DatabaseError;
        m_cbMsgID = CallbackStatus::Schedule::_3;
        m_cbMsg = CallbackStatus::Schedule::_3_Desc_DatabaseError;
    }
    //解析参数失败
    else if(rState == Data_Authority::_5) {
        qDebug() << Data_Authority::_5_DESC_ParamParseError;
        m_cbMsgID = CallbackStatus::Schedule::_4;
        m_cbMsg = CallbackStatus::Schedule::_4_Desc_ParamParseError;
    }
    //没有可下发的节点服务器
    else if(rState == Data_Authority::_6) {
        qDebug() << Data_Authority::_6_DESC_NoderIsNull;
        m_cbMsgID = CallbackStatus::Schedule::_5;
        m_cbMsg = CallbackStatus::Schedule::_5_Desc_SeiviceIsNull;
    }
    //解析返回数据失败
    else if(rState == Data_Authority::_8) {
        qDebug() << Data_Authority::_8_DESC_ParseDataError;
        m_cbMsgID = CallbackStatus::Schedule::_6;
        m_cbMsg = CallbackStatus::Schedule::_6_Desc_ParseDataError;
    }
    //自定义校验 服务端获取参数为空
    else if(rState == Data_Authority::_7) {
        qDebug() << Data_Authority::_7_DESC_ParamsHasNullValue;
        m_cbMsgID = CallbackStatus::Schedule::_7;
        m_cbMsg = CallbackStatus::Schedule::_7_Desc_ParamsHasNullValue;
    }
    //操作成功
    else if(rState == Data_Authority::_0) {
        ok = ScheduleUtil::taskEntinyFromJson(task,result);
        if (!ok)
        {
            qDebug("解析返回数据失败");
            m_cbMsgID = CallbackStatus::Schedule::_6;
            m_cbMsg = CallbackStatus::Schedule::_6_Desc_ParseDataError;
        }
        else {
            m_cbMsgID = CallbackStatus::Schedule::_0;
        }

    }else{}

    QMetaObject::invokeMethod(m_object,"on_itemtaskCallback",Qt::QueuedConnection,
                              Q_ARG(qint32,m_cbMsgID),
                              Q_ARG(QString,m_cbMsg),
                              Q_ARG(CsRScheduleTask,task)
                              );

     sender->destory();
}

