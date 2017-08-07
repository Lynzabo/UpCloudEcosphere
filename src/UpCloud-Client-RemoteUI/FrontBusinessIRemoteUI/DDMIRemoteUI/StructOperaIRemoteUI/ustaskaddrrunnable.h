#ifndef UPDATESTRUCTTASKADDRRUNNABLE_H
#define UPDATESTRUCTTASKADDRRUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "structoperairemoteui_global.h"
#include "baseiremote.h"

class STRUCTOPERAIREMOTEUISHARED_EXPORT UpdateStructTaskAddrRunnable : public QRunnable
{
public:
    UpdateStructTaskAddrRunnable(QObject* object = 0);
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

#endif // UPDATESTRUCTTASKADDRRUNNABLE_H
