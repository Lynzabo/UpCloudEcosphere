#ifndef DELSCHEDULETASKFILERUNNABLE_H
#define DELSCHEDULETASKFILERUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "scheduleoperairemoteui_global.h"
#include "baseiremote.h"

class SCHEDULEOPERAIREMOTEUISHARED_EXPORT DelScheduleTaskFileRunnable : public QRunnable
{
public:
    DelScheduleTaskFileRunnable(QObject *object = 0);
    void setFilesInfo(const QStringList &uuids);
protected:
    void run();
private:
    qint32 m_cbMsgID;
    QString m_cbMsg;
    QObject* m_object;
    QStringList m_uuids;
};

#endif // DELSCHEDULETASKFILERUNNABLE_H
