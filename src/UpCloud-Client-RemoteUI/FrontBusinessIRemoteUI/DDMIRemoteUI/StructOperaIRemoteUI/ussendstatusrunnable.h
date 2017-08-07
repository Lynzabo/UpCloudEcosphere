#ifndef UPDATESTRUCTSENDSTATUSRUNNABLE_H
#define UPDATESTRUCTSENDSTATUSRUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "structoperairemoteui_global.h"
#include "baseiremote.h"

class STRUCTOPERAIREMOTEUISHARED_EXPORT UpdateStructSendStatusRunnable : public QRunnable
{
public:
    UpdateStructSendStatusRunnable(QObject* object = 0);
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

#endif // UPDATESTRUCTSENDSTATUSRUNNABLE_H
