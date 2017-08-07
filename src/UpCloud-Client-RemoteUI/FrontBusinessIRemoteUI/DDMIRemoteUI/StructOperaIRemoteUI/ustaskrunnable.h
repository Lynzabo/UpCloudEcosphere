#ifndef UPDATESTRUCTTASKRUNNABLE_H
#define UPDATESTRUCTTASKRUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "structoperairemoteui_global.h"
#include "baseiremote.h"
#include "../../../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrstask.h"

class STRUCTOPERAIREMOTEUISHARED_EXPORT UpdateStructTaskRunnable : public QRunnable
{
public:
    UpdateStructTaskRunnable(QObject *object = 0);
    void setTaskList(const QList<CsRStructTask> &taskList);
protected:
    void run();
private:
    QObject *m_object;
    //消息ID
    qint32 m_cbMsgId;
    //消息内容
    QString m_cbMsg;
    QList<CsRStructTask> m_taskList;
};

#endif // UPDATESTRUCTTASKRUNNABLE_H
