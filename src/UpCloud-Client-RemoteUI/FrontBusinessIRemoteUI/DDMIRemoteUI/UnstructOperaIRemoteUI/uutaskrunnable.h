#ifndef UPDATEUNSTRUCTTASKRUNNABLE_H
#define UPDATEUNSTRUCTTASKRUNNABLE_H
#include <QtCore>
#include "base.h"
#include "baseiremote.h"
#include "duplex.h"
#include "unstructoperairemoteui_global.h"
#include "avro.h"
#include "../../../../UpCloud-Service-Center/FrontBusinessIServer/DDMIServer/UnstructOperaIServer/util/unstructutil.h"
class UNSTRUCTOPERAIREMOTEUISHARED_EXPORT UpdateUnstructTaskRunnable : public QRunnable
{
public:
    UpdateUnstructTaskRunnable(QObject* object = 0);
    void setTaskList(const QList<CsRUnstructTask> &list);
protected:
    void run();

private:
    QObject* m_object;
    qint32 cbMsgId;
    QString cbMsg;
    QList<CsRUnstructTask> m_taskList;
};

#endif // UPDATEUNSTRUCTTASKRUNNABLE_H
