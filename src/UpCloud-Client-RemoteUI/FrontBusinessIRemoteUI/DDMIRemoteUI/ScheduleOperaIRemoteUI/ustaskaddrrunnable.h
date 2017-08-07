#ifndef UPDATESCHETASKADDRRUNNABLE_H
#define UPDATESCHETASKADDRRUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "scheduleoperairemoteui_global.h"
#include "baseiremote.h"

class SCHEDULEOPERAIREMOTEUISHARED_EXPORT UpdateScheTaskAddrRunnable : public QRunnable
{
public:
    UpdateScheTaskAddrRunnable(QObject* object = 0);
    void setScheAddr(const QString &taskUUID,const QStringList &nodes,const quint8 state,const QString &time = "");
protected:
    void run();
private:
    qint32 m_cbMsgID;
    QString m_cbMsg;
    QObject* m_object;
    QString m_taskUuid;
    QStringList m_nodes;
    quint8 m_state;
    QString m_time;
};

#endif // UPDATESCHETASKADDRRUNNABLE_H
