#ifndef ADDSTRUCTTASKFILERUNNABLE_H
#define ADDSTRUCTTASKFILERUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "structoperairemoteui_global.h"
#include "baseiremote.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendfiles.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/vcssendaddr.h"
#include <QList>

class STRUCTOPERAIREMOTEUISHARED_EXPORT AddStructTaskFileRunnable : public QRunnable
{
public:
    AddStructTaskFileRunnable(QObject* object = 0);
protected:
    void run();
public:
    void setAddCondition(const QString &taskuuid,const QList<CsRStructSendFiles> &taskList,const QList<VCsRStructSendAddr> &addrList);
private:
    QObject* m_object;
    qint32 m_cbMsgId;
    QString m_cbMsg;
    QList<CsRStructSendFiles> m_fileList;
    QString m_taskUuid;
    QList<VCsRStructSendAddr> m_addrList;
};

#endif // ADDSTRUCTTASKFILERUNNABLE_H
