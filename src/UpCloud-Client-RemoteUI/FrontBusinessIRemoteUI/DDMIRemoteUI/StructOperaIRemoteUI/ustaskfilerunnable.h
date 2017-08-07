#ifndef UPDATESTRUCTTASKFILERUNNABLE_H
#define UPDATESTRUCTTASKFILERUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "structoperairemoteui_global.h"
#include "baseiremote.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendfiles.h"

class STRUCTOPERAIREMOTEUISHARED_EXPORT UpdateStructTaskFileRunnable : public QRunnable
{
public:
    UpdateStructTaskFileRunnable(QObject* object = 0);
protected:
    void run();
public:
    void setUpdateInfo(const QStringList &uuids,const QString &taskuuid,const quint8 &state);
private:
    QObject* m_object;
    qint32 m_cbMsgId;
    QString m_cbMsg;
    QStringList m_uuids;
    QString m_taskUuid;
    quint8 m_state;
};

#endif // UPDATESTRUCTTASKFILERUNNABLE_H
