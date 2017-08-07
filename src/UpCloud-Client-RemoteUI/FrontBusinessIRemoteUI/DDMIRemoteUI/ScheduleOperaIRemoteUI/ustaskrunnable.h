#ifndef UDATESCHEDULETASKRUNNABLE_H
#define UDATESCHEDULETASKRUNNABLE_H
#include "base.h"
#include <QtCore>
#include "avro.h"
#include "duplex.h"
#include "baseiremote.h"
#include "scheduleoperairemoteui_global.h"
#include "../../UpCloud-Service-Center/BusinessIServer/ScheduleIServer/bean/csrsctask.h"
class SCHEDULEOPERAIREMOTEUISHARED_EXPORT UpdateScheduleTaskRunnable : public QRunnable
{
public:
    UpdateScheduleTaskRunnable(QObject* object = 0);
    void setTaskList(const QList<CsRScheduleTask> &list);
protected:
    void run();
private:
    qint32 m_cbMsgID;
    QString m_cbMsg;
    QObject* m_object;
    QList<CsRScheduleTask> m_taskList;
};

#endif // UDATESCHEDULETASKRUNNABLE_H
