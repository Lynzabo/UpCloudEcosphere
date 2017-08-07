#include "iutaskrunnable.h"
#include "../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrutask.h"
#include "../../../../UpCloud-Service-Center/FrontBusinessIServer/DDMIServer/UnstructOperaIServer/util/unstructutil.h"
using namespace Environment::Datagram::UI_Ctrl::Opera_Type;
using QtJson::JsonObject;
using QtJson::JsonArray;
using namespace Environment::Duplex_Interaction;
using namespace RemoteUIEnvironment;
ItemUnstructTaskRunnable::ItemUnstructTaskRunnable(QObject *object):m_object(object)
{
    cbMsgId = 0;
    cbMsg.clear();
    //注册CsRUnstructTask元数据
    qRegisterMetaType<CsRUnstructTask>("CsRUnstructTask");
}

void ItemUnstructTaskRunnable::setTaskUUID(const QString &uuid)
{
    m_uuid = uuid;
}

void ItemUnstructTaskRunnable::run()
{
    CsRUnstructTask task;
    JsonObject jsonParams;
    jsonParams["taskId"] = m_uuid;
    QString params = QtJson::serialize(jsonParams);

    //1.准备消息发送端
    DPSender* sender = UpCloudDuplexFactory::getInstance().createDPSender();
    if(!sender) {
        return;
    }
    //2.请求数据
    sender->setExecType(Control_Module::Unstruct_itemTask);
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
    //FATAL
    //反序列化处理可能不全面
    else if(rState == Data_Authority::_0) {
        bool ok = UnstructUtil::taskEntityFromjsonStr(task,result);
        if (!ok)
        {
            qDebug("解析返回数据失败");
            cbMsgId = CallbackStatus::Unstruct::_6;
            cbMsg = CallbackStatus::Unstruct::_6_Desc_ParseDataError;
        }
        {
            cbMsgId = CallbackStatus::Unstruct::_0;
            //cbMsg = QObject::trUtf8("任务名称:%1,任务编号:%2,创建人名:%3").arg(task.getTaskName()).arg(task.getTaskNum()).arg(task.getInsertor());
        }
    }else{}
    QMetaObject::invokeMethod(m_object,"on_itemtaskCallback",Qt::QueuedConnection,
                              Q_ARG(qint32,cbMsgId),
                              Q_ARG(QString,cbMsg),
                              Q_ARG(CsRUnstructTask,task)
                              );
    sender->destory();
}

