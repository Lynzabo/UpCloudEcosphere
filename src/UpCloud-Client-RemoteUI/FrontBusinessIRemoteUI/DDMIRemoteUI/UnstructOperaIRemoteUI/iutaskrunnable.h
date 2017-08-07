#ifndef ITEMUNSTRUCTTASKRUNNABLE_H
#define ITEMUNSTRUCTTASKRUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "unstructoperairemoteui_global.h"
#include "baseiremote.h"
class UNSTRUCTOPERAIREMOTEUISHARED_EXPORT ItemUnstructTaskRunnable : public QRunnable
{
public:
    ItemUnstructTaskRunnable(QObject *object = 0);
    void setTaskUUID(const QString & uuid);
protected:
    void run();

private:
    QObject *m_object;
    //消息ID
    qint32 cbMsgId;
    //消息内容
    QString cbMsg;
    //查询任务UUID
    QString m_uuid;
};

#endif // ITEMUNSTRUCTTASKRUNNABLE_H
