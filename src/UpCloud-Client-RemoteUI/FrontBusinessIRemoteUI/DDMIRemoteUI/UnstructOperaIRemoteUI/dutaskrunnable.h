#ifndef DELUNSTRUCTTASKSEVLET_H
#define DELUNSTRUCTTASKSEVLET_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "unstructoperairemoteui_global.h"
#include "baseiremote.h"
using QtJson::JsonArray;
class UNSTRUCTOPERAIREMOTEUISHARED_EXPORT DelUnstructTaskRunnable : public QRunnable
{
public:
    DelUnstructTaskRunnable(QObject *object = 0);
protected:
    void run();
public:
    void setTaskUuids(const JsonArray &json);
private:
    QObject* m_object;
    qint32 m_cbMsgId;
    QString m_cbMsg;
    JsonArray m_uuids;
};

#endif // DELUNSTRUCTTASKSEVLET_H
