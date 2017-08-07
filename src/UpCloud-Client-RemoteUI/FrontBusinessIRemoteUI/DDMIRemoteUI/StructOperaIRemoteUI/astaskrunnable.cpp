#include "astaskrunnable.h"
#include "../../../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrstask.h"
using namespace Environment::Datagram::UI_Ctrl::Opera_Type;
using QtJson::JsonObject;
using QtJson::JsonArray;
using namespace Environment::Duplex_Interaction;
using namespace RemoteUIEnvironment;


AddStructTaskRunnable::AddStructTaskRunnable(QObject *object):m_object(object)
{
    cbMsgId = 0;
    cbMsg.clear();
    //注册CsRUnstructTask元数据
    qRegisterMetaType<CsRStructTask>("CsRStructTask");
    qRegisterMetaType<QList<CsRStructTask> >("QList<CsRStructTask>");
}

void AddStructTaskRunnable::setAddCondition(const CsRStructTask &task, const QList<CsRStructSendAddr> &addrInfoList, const QList<CsRStructSendFiles> &fileInfoList, const QList<CsRStructSendStatus> &statusInfoList)
{

    m_task = task;
    m_addrInfoList = addrInfoList;
    m_fileInfoList = fileInfoList;
    m_statusInfoList = statusInfoList;
}


void AddStructTaskRunnable::run()
{
    CsRStructTask task;
    quint8 rState;
    QString result;result.clear();
    QString params;params.clear();
    JsonObject json;
    QString taskStr;
    QString addrStr;
    QString fileStr;
    QString statusStr;
    StructUtil::taskEntinyTojsonStr(taskStr,m_task);
    json["taskStr"] = taskStr;
    StructUtil::taskEntinyTojsonStr(addrStr,m_addrInfoList);
    json["addrStr"] = addrStr;
    StructUtil::taskEntinyTojsonStr(fileStr,m_fileInfoList);
    json["fileStr"] = fileStr;
    StructUtil::taskSendStatusEntityTojsonStr(statusStr,m_statusInfoList);
    json["statusStr"] = statusStr;
    params = QtJson::serialize(json);
   //准备消息发送端
   DPSender* sender = UpCloudDuplexFactory::getInstance().createDPSender();
   if(!sender) {

       return;
   }
   sender->setExecType(Control_Module::Struct_addTask);
   sender->setParams(params);

   //准备结果集
   DPResult* resultSet = sender->doSendBySync();
   rState = resultSet->getRState();
   result = resultSet->getRContent();


   //通用校验
   //地址无效
   if(rState == Data_Authority::_2) {
       qDebug() << Data_Authority::_2_DESC_AddrIsInvalid;
       cbMsgId = CallbackStatus::Struct::_1;
       cbMsg = CallbackStatus::Struct::_1_Desc_AddrIsInvalid;
   }
   //未授权访问
   else if(rState == Data_Authority::_1) {
       qDebug() << Data_Authority::_1_DESC_Unauthorized;
       cbMsgId = CallbackStatus::Struct::_2;
       cbMsg = CallbackStatus::Struct::_2_Desc_Unauthorized;
   }
   //数据库操作失败
   else if(rState == Data_Authority::_4) {
       qDebug() << Data_Authority::_4_DESC_DatabaseError;
       cbMsgId = CallbackStatus::Struct::_3;
       cbMsg = CallbackStatus::Struct::_3_Desc_DatabaseError;
   }
   //解析参数失败
   else if(rState == Data_Authority::_5) {
       qDebug() << Data_Authority::_5_DESC_ParamParseError;
       cbMsgId = CallbackStatus::Struct::_4;
       cbMsg = CallbackStatus::Struct::_4_Desc_ParamParseError;
   }
   //没有可下发的节点服务器
   else if(rState == Data_Authority::_6) {
       qDebug() << Data_Authority::_6_DESC_NoderIsNull;
       cbMsgId = CallbackStatus::Struct::_5;
       cbMsg = CallbackStatus::Struct::_5_Desc_SeiviceIsNull;
   }
   //解析返回数据失败
   else if(rState == Data_Authority::_8) {
       qDebug() << Data_Authority::_8_DESC_ParseDataError;
       cbMsgId = CallbackStatus::Struct::_6;
       cbMsg = CallbackStatus::Struct::_6_Desc_ParseDataError;
   }
   //自定义校验 服务端获取参数为空
   else if(rState == Data_Authority::_7) {
       qDebug() << Data_Authority::_7_DESC_ParamsHasNullValue;
       cbMsgId = CallbackStatus::Struct::_7;
       cbMsg = CallbackStatus::Struct::_7_Desc_ParamsHasNullValue;
   }
   //操作成功
   else if(rState == Data_Authority::_0) {
           cbMsgId = CallbackStatus::Struct::_0;
   }else{}
   QMetaObject::invokeMethod(m_object,"on_itemtaskCallback",Qt::QueuedConnection,
                             Q_ARG(qint32,cbMsgId),
                             Q_ARG(QString,cbMsg),
                             Q_ARG(bool,false)
                             );

   sender->destory();
}


