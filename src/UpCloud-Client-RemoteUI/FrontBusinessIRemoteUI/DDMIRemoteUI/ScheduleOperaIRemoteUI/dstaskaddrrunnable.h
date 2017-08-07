#ifndef DELSCHEDULETASKADDRRUNNABLE_H
#define DELSCHEDULETASKADDRRUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "scheduleoperairemoteui_global.h"
#include "baseiremote.h"

class SCHEDULEOPERAIREMOTEUISHARED_EXPORT DelScheduleTaskAddrRunnable : public QRunnable
{
public:
    DelScheduleTaskAddrRunnable(QObject* object = 0);
    void setAddrInfo(const QString &taskUuid,const QStringList &clientUuids);
protected:
    void run();
private:
    qint32 m_cbMsgID;
    QString m_cbMsg;
    QObject* m_object;
    QString m_taskUuid;
    QStringList m_clientUuids;
};

#endif // DELSCHEDULETASKADDRRUNNABLE_H
