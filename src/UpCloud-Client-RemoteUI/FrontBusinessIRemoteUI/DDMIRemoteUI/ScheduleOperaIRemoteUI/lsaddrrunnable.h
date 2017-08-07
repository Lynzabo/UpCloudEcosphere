#ifndef LISTSCHEDULEADDRRUNNABLE_H
#define LISTSCHEDULEADDRRUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "scheduleoperairemoteui_global.h"
#include "baseiremote.h"

class SCHEDULEOPERAIREMOTEUISHARED_EXPORT ListScheduleAddrRunnable : public QRunnable
{
public:
    ListScheduleAddrRunnable(QObject* object = 0);
    void setTaskUuid(const QString &taskUuid);
protected:
    void run();
private:
    qint32 m_cbMsgID;
    QString m_cbMsg;
    QObject* m_object;
    QString m_taskUuid;
};

#endif // LISTSCHEDULEADDRRUNNABLE_H
