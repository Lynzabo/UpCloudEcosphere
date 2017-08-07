#include "astaskaddrrunnable.h"
#include "avro.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendaddr.h"
#include "../../UpCloud-Service-Center/FrontBusinessIServer/DDMIServer/StructOperaIServer/util/structutil.h"
using namespace Environment::Datagram::UI_Ctrl::Opera_Type;
using namespace Environment::Duplex_Interaction;
using QtJson::JsonArray;
using QtJson::JsonObject;
using namespace RemoteUIEnvironment;

AddStructTaskAddrRunnable::AddStructTaskAddrRunnable(QObject *object):m_object(object)
{
    m_cbMsg.clear();
    m_cbMsgId = 0;
    qRegisterMetaType<CsRStructSendAddr>("CsRStructSendAddr");
    qRegisterMetaType<QList<CsRStructSendAddr> >("QList<CsRStructSendAddr>");
}

void AddStructTaskAddrRunnable::run()
{
    quint8 rState;
    QString result;result.clear();
    QString uuidStr = QtJson::serialize(m_uuids);
    QString desStr = QtJson::serialize(m_groupDes);
    JsonObject json;
    json.insert("uuids",uuidStr);
    json.insert("taskuuid",m_taskUuid);
    json.insert("description",desStr);
    QString params = QtJson::serialize(json);
    //准备消息发送端
    DPSender* sender = UpCloudDuplexFactory::getInstance().createDPSender();
    if(!sender) {
        qDebug() << trs("消息发送端 错误");
        return;
    }
    //准备数据
    sender->setExecType(Control_Module::Struct_addTaskNode);
    sender->setParams(params);

    //准备结果集
    DPResult* resultSet = sender->doSendBySync();
    rState = resultSet->getRState();
    result = resultSet->getRContent();
    //通用效验
    //地址无效
    if(rState == Data_Authority::_2) {
        qDebug() << Data_Authority::_2_DESC_AddrIsInvalid;
        m_cbMsgId = CallbackStatus::Struct::_1;
        m_cbMsg = CallbackStatus::Struct::_1_Desc_AddrIsInvalid;
    }
    //未授权访问
    else if(rState == Data_Authority::_1) {
        qDebug() << Data_Authority::_1_DESC_Unauthorized;
        m_cbMsgId = CallbackStatus::Struct::_2;
        m_cbMsg = CallbackStatus::Struct::_2_Desc_Unauthorized;
    }
    //数据库操作失败
    else if(rState == Data_Authority::_4) {
        qDebug() << Data_Authority::_4_DESC_DatabaseError;
        m_cbMsgId = CallbackStatus::Struct::_3;
        m_cbMsg = CallbackStatus::Struct::_3_Desc_DatabaseError;
    }
    //解析参数失败
    else if(rState == Data_Authority::_5) {
        qDebug() << Data_Authority::_5_DESC_ParamParseError;
        m_cbMsgId = CallbackStatus::Struct::_4;
        m_cbMsg = CallbackStatus::Struct::_4_Desc_ParamParseError;
    }
    //没有可下发的节点服务器
    else if(rState == Data_Authority::_6) {
        qDebug() << Data_Authority::_6_DESC_NoderIsNull;
        m_cbMsgId = CallbackStatus::Struct::_5;
        m_cbMsg = CallbackStatus::Struct::_5_Desc_SeiviceIsNull;
    }
    //解析返回数据失败
    else if(rState == Data_Authority::_8) {
        qDebug() << Data_Authority::_8_DESC_ParseDataError;
        m_cbMsgId = CallbackStatus::Struct::_6;
        m_cbMsg = CallbackStatus::Struct::_6_Desc_ParseDataError;
    }
    //自定义校验 服务端获取参数为空
    else if(rState == Data_Authority::_7) {
        qDebug() << Data_Authority::_7_DESC_ParamsHasNullValue;
        m_cbMsgId = CallbackStatus::Struct::_7;
        m_cbMsg = CallbackStatus::Struct::_7_Desc_ParamsHasNullValue;
    }
    else if(rState == Data_Authority::_9) {
        qDebug() << Data_Authority::_9_DESC_RecordIsExsit;
        m_cbMsgId = CallbackStatus::Struct::_8;
        m_cbMsg = CallbackStatus::Struct::_8_Desc_RecordIsExist;
    }
    //操作成功
    else if(rState == Data_Authority::_0 ) {

        m_cbMsgId = CallbackStatus::Struct::_0;


    }else{}
    QMetaObject::invokeMethod(m_object,"on_itemtaskCallback",Qt::QueuedConnection,
                              Q_ARG(qint32,m_cbMsgId),
                              Q_ARG(QString,m_cbMsg)
            );


    sender->destory();
}

void AddStructTaskAddrRunnable::setAddCondition(const QStringList &uuids, const QString &taskuuid, const QStringList &groupDes)
{
    m_taskUuid = taskuuid;
    m_uuids = uuids;
    m_groupDes = groupDes;
}

