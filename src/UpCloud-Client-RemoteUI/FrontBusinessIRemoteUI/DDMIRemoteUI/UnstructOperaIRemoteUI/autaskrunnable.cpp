#include "autaskrunnable.h"
#include "../../../../UpCloud-Service-Center/FrontBusinessIServer/DDMIServer/UnstructOperaIServer/util/unstructutil.h"

using namespace Environment::Datagram::UI_Ctrl::Opera_Type;
using QtJson::JsonObject;
using QtJson::JsonArray;
using namespace Environment::Duplex_Interaction;
using namespace RemoteUIEnvironment;


AddUnstructTaskRunnable::AddUnstructTaskRunnable(QObject *object):m_object(object)
{
    cbMsgId = 0;
    cbMsg.clear();
    //注册CsRUnstructTask元数据
    qRegisterMetaType<CsRUnstructTask>("CsRUnstructTask");
    qRegisterMetaType<QList<CsRUnstructTask> >("QList<CsRUnstructTask>");

}

void AddUnstructTaskRunnable::setAddCondition(const CsRUnstructTask &task, const QList<CsRUnstructSendAddr> &addrInfoList,
                                              const QList<CsRUnstructSendFiles> &fileInfoList,
                                              const QList<CsRUnstructSendStatus> &statusInfoList)
{
    m_task = task;
    m_addrInfoList = addrInfoList;
    m_fileInfoList = fileInfoList;
    m_statusInfoList = statusInfoList;
}

void AddUnstructTaskRunnable::run()
{

    quint8 rState;
    QString result;result.clear();
    QString params;params.clear();

    JsonObject json;
    QString taskStr;
    QString addrStr;
    QString fileStr;
    QString statusStr;
    UnstructUtil::taskEntityTojsonStr(taskStr,m_task);
    json["taskStr"] = taskStr;
    UnstructUtil::taskAddrEntityTojsonStr(addrStr,m_addrInfoList);
    json["addrStr"] = addrStr;
    UnstructUtil::taskAddrFileEntityTojsonStr(fileStr,m_fileInfoList);
    json["fileStr"] = fileStr;
    UnstructUtil::taskSendStatusEntityTojsonStr(statusStr,m_statusInfoList);
    json["statusStr"] = statusStr;
    params = QtJson::serialize(json);
    //准备消息发送端
    DPSender* sender = UpCloudDuplexFactory::getInstance().createDPSender();
    if(!sender) {

        return;
    }
    sender->setExecType(Control_Module::Unstruct_addTask);
    sender->setParams(params);

    //准备结果集
    DPResult* resultSet = sender->doSendBySync();
    rState = resultSet->getRState();
    result = resultSet->getRContent();


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
    else if(rState == Data_Authority::_9) {
        cbMsgId = CallbackStatus::Unstruct::_8;
        cbMsg = CallbackStatus::Unstruct::_8_Desc_RecordIsExist;
    }
    //操作成功
    else if(rState == Data_Authority::_0) {
            cbMsgId = CallbackStatus::Unstruct::_0;
    }else{}
    QMetaObject::invokeMethod(m_object,"on_itemtaskCallback",Qt::QueuedConnection,
                              Q_ARG(qint32,cbMsgId),
                              Q_ARG(QString,cbMsg),
                              Q_ARG(bool,false)
                              );

    sender->destory();

}

