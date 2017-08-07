#ifndef ITEMSCHEDULETASKRUNNABLE_H
#define ITEMSCHEDULETASKRUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "scheduleoperairemoteui_global.h"
#include "baseiremote.h"

class SCHEDULEOPERAIREMOTEUISHARED_EXPORT ItemScheduleTaskRunnable : public QRunnable
{
public:
    ItemScheduleTaskRunnable(QObject* object = 0);
    void setTaskUuid(const QString &taskUuid);
protected:
    void run();
private:
    qint32 m_cbMsgID;
    QString m_cbMsg;
    QObject* m_object;
    QString m_taskUuid;
};

#endif // ITEMSCHEDULETASKRUNNABLE_H
