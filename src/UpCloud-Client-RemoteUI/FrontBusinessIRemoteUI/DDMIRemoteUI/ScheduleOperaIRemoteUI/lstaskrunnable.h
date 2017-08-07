#ifndef LISTCSRSCHEDULETASKRUNNABLE_H
#define LISTCSRSCHEDULETASKRUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "scheduleoperairemoteui_global.h"
#include "baseiremote.h"
class SCHEDULEOPERAIREMOTEUISHARED_EXPORT ListCsRScheduleTaskRunnable : public QRunnable
{
public:
    ListCsRScheduleTaskRunnable(QObject* object = 0);
    void setScheduleDirinfo(const QVariantMap &params);
protected:
    void run();
private:
    qint32 m_cbMsgID;
    QString m_cbMsg;
    QObject* m_object;
    QVariantMap m_params;
};

#endif // LISTCSRSCHEDULETASKRUNNABLE_H
