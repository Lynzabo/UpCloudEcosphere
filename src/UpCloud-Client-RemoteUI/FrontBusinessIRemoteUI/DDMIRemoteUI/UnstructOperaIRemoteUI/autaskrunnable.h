#ifndef AUTASKRUNNABLE_H
#define AUTASKRUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "unstructoperairemoteui_global.h"
#include "../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrutask.h"
#include "../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendaddr.h"
#include "../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendfiles.h"
#include "../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendstatus.h"
#include "baseiremote.h"
class UNSTRUCTOPERAIREMOTEUISHARED_EXPORT AddUnstructTaskRunnable : public QRunnable
{
public:
    AddUnstructTaskRunnable(QObject *object = 0);
    void setAddCondition(const CsRUnstructTask &task,const QList<CsRUnstructSendAddr> &addrInfoList,
                         const QList<CsRUnstructSendFiles> &fileInfoList,
                         const QList<CsRUnstructSendStatus> &statusInfoList);
protected:
    void run();
private:
    QObject *m_object;
    //消息ID
    qint32 cbMsgId;
    //消息内容
    QString cbMsg;
    //封装消息实体
    CsRUnstructTask m_task;
    QList<CsRUnstructSendAddr> m_addrInfoList;
    QList<CsRUnstructSendFiles>  m_fileInfoList;
    QList<CsRUnstructSendStatus> m_statusInfoList;
};

#endif // AUTASKRUNNABLE_H
