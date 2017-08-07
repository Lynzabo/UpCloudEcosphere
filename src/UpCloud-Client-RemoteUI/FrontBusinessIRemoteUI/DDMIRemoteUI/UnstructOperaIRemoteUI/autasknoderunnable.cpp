#include "autasknoderunnable.h"
#include "../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendaddr.h"
#include "../../../../UpCloud-Service-Center/FrontBusinessIServer/DDMIServer/UnstructOperaIServer/util/unstructutil.h"
using namespace Environment::Datagram::UI_Ctrl::Opera_Type;
using QtJson::JsonObject;
using QtJson::JsonArray;
using namespace Environment::Duplex_Interaction;
using namespace RemoteUIEnvironment;
AddUnstructTaskNodeServlet::AddUnstructTaskNodeServlet(QObject *object):m_object(object)
{
    m_cbMsgId = 0;
    m_cbMsg.clear();
    qRegisterMetaType<CsRUnstructSendAddr>("CsRUnstructSendAddr");
}

void AddUnstructTaskNodeServlet::run()
{

//    CsRUnstructSendAddr task;
//    JsonObject json;
//    json["client_uuid"] = "10.0.0.888";
//    json["state"] = "8";
//    json["error"] = "888";
//    QString params = QtJson::serialize(json);
//    //准备消息发送端
//    DPSender* sender = UpCloudDuplexFactory::getInstance().createDPSender();
//    if(!sender) {
//        qDebug() << trs("准备消息发送端错误");
//        return;
//    }

//    sender->setExecType(Control_Module::Unstruct_addTaskNode);
//    sender->setParams(params);

//    //准备结果集
//    DPResult* resultSet = sender->doSendBySync();
//    if(!resultSet) {
//        qDebug() << resultSet;
//        return;
//    }

//    quint8 rState = resultSet->getRState();
//    QString result = resultSet->getRContent();
//    //TODO
//    ////添加出错类型的判断



//    //解析参数列表失败
//    if(rState == Data_Authority::_5) {
//        qDebug() << Data_Authority::_5_DESC_SeiviceIsNull;
//        m_cbMsgId = CallbackStatus::Unstruct::_4;
//        m_cbMsg = CallbackStatus::Unstruct::_4_Desc_ParamParseError;
//    }
//    //操作数据库失败
//    else if(rState == Data_Authority::_4) {
//        qDebug() << Data_Authority::_4_DESC_SeiviceIsNull;
//        m_cbMsgId = CallbackStatus::Unstruct::_3;
//        m_cbMsg = CallbackStatus::Unstruct::_3_Desc_DatabaseError;
//    }
//    //未找到后台服务
//    else if(rState ==Data_Authority::_3 ) {
//        qDebug() << Data_Authority::_3_DESC_SeiviceIsNull;
//        m_cbMsgId = CallbackStatus::Unstruct::_5;
//        m_cbMsg = CallbackStatus::Unstruct::_5_Desc_SeiviceIsNull;
//    }
//    //访问地址无效
//    else if(rState == Data_Authority::_2) {
//        qDebug() << Data_Authority::_2_DESC_AddrIsInvalid;
//        m_cbMsgId = CallbackStatus::Unstruct::_1;
//        m_cbMsg = CallbackStatus::Unstruct::_1_Desc_AddrIsInvalid;
//    }
//    //未授权访问地址
//    else if(rState == Data_Authority::_1) {
//        qDebug() << Data_Authority::_1_DESC_Unauthorized;
//        m_cbMsgId = CallbackStatus::Unstruct::_2;
//        m_cbMsg = CallbackStatus::Unstruct::_2_Desc_Unauthorized;
//    }
//    //成功
//    else if(rState == Data_Authority::_0) {

//        m_cbMsg = CallbackStatus::Unstruct::_0_Desc_SUCCESS;
//        m_cbMsgId = CallbackStatus::Unstruct::_0;

//        //反序列化
//        bool ok;

//        ok = UnstructUtil::taskAddrEntityFromjsonStr(task,result);
//        if(!ok) {
//            qDebug() << trs("反序列化失败");
//            m_cbMsgId = CallbackStatus::Unstruct::_6;
//            m_cbMsg = CallbackStatus::Unstruct::_6_Desc_ParseDataError;
//        }
//        else {
//            m_cbMsgId = CallbackStatus::Unstruct::_0;

//            m_cbMsg = QObject::trUtf8("任务编号:%1,节点地址:%2").arg(task.getUuid()).arg(task.getClientUuid());
//            //qDebug(m_cbMsg);
//        }

//    }
//    else {}
//    QMetaObject::invokeMethod(m_object,"on_itemtaskCallback",Qt::QueuedConnection,
//                              Q_ARG(qint32,m_cbMsgId),
//                              Q_ARG(QString,m_cbMsg),
//                              Q_ARG(CsRUnstructSendAddr,task)
//                              );
//    sender->destory();

}
