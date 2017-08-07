#ifndef AUTASKFILERUNNABLE_H
#define AUTASKFILERUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "unstructoperairemoteui_global.h"
#include "baseiremote.h"
#include "../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendfiles.h"
#include "../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/vcsrusendaddr.h"
class UNSTRUCTOPERAIREMOTEUISHARED_EXPORT AddUnstructTaskFileRunnable:public QRunnable
{
public:
    AddUnstructTaskFileRunnable(QObject *object = 0);
protected:
    void run();
public:
    void setAddCondition(const QString &taskuuid,const QList<CsRUnstructSendFiles> &taskList,const QList<VCsRUnstructSendAddr> &addrList);
private:
    QObject* m_object;
    qint32 m_cbMsgId;
    QString m_cbMsg;
    QList<CsRUnstructSendFiles> m_taskList;
    QString m_taskUuid;
    QList<VCsRUnstructSendAddr> m_addrList;
};
#endif // AUTASKFILERUNNABLE_H
