#ifndef DELSCHEDULETASKRUNNABLE_H
#define DELSCHEDULETASKRUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "scheduleoperairemoteui_global.h"
#include "baseiremote.h"


class SCHEDULEOPERAIREMOTEUISHARED_EXPORT DelScheduleTaskRunnable : public QRunnable
{
public:
    DelScheduleTaskRunnable(QObject* object = 0);
    void setTaskUuid(const QStringList &uuids);
protected:
    void run();
private:
    qint32 m_cbMsgID;
    QString m_cbMsg;
    QObject* m_object;
    QStringList m_uuids;
};

#endif // DELSCHEDULETASKRUNNABLE_H
