#ifndef UPDATEUNSTRUCTTASKADDRRUNNABLE_H
#define UPDATEUNSTRUCTTASKADDRRUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "unstructoperairemoteui_global.h"
#include "baseiremote.h"

class UNSTRUCTOPERAIREMOTEUISHARED_EXPORT UpdateUnstructTaskAddrRunnable : public QRunnable
{
public:
    UpdateUnstructTaskAddrRunnable(QObject* object = 0);
protected:
    void run();
public:
    void setUpdateState(const QStringList &clientUuids,const QString &taskuuid,const quint8 state);
private:
    QObject* m_object;
    qint32 m_cbMsgId;
    QString m_cbMsg;
    QStringList m_uuids;
    QString m_taskUuid;
    quint8 m_state;
};

#endif // UPDATEUNSTRUCTTASKADDRRUNNABLE_H
