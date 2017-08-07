#ifndef UPDATEUNSTRUCTSENDSTATUSRUNNABLE_H
#define UPDATEUNSTRUCTSENDSTATUSRUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "unstructoperairemoteui_global.h"
#include "baseiremote.h"

class UNSTRUCTOPERAIREMOTEUISHARED_EXPORT UpdateUnstructSendStatusRunnable : public QRunnable
{
public:
    UpdateUnstructSendStatusRunnable(QObject* object = 0);
protected:
    void run();
public:
    void setUpdateState(const QStringList &uuids,const QString &taskUuid,const quint8 state);
private:
    QObject* m_object;
    qint32 m_cbMsgId;
    QString m_cbMsg;
    QStringList m_uuids;
    quint8 m_state;
    QString m_taskUuid;
};

#endif // UPDATEUNSTRUCTSENDSTATUSRUNNABLE_H
