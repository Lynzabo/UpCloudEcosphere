#ifndef DELSTRUCTTASKRUNNABLE_H
#define DELSTRUCTTASKRUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "structoperairemoteui_global.h"
#include "baseiremote.h"
using QtJson::JsonArray;
class STRUCTOPERAIREMOTEUISHARED_EXPORT DelStructTaskRunnable : public QRunnable
{
public:
    DelStructTaskRunnable(QObject* object = 0);
protected:
    void run();
public:
    void setTaskInfo(const JsonArray &json);
private:
    QObject* m_object;
    qint32 m_cbMsgId;
    QString m_cbMsg;
    JsonArray m_uuids;
};

#endif // DELSTRUCTTASKRUNNABLE_H
