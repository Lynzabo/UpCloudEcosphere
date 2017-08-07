#ifndef DELSTRUCTTASKADDRRUNNABLE_H
#define DELSTRUCTTASKADDRRUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "structoperairemoteui_global.h"
#include "baseiremote.h"
using QtJson::JsonArray;

class STRUCTOPERAIREMOTEUISHARED_EXPORT DelStructTaskAddrRunnable : public QRunnable
{
public:
    DelStructTaskAddrRunnable(QObject* object = 0);
protected:
    void run();
public:
    void setAddrInfo(const JsonArray &json,const QString &taskuuid);
private:
    QObject* m_object;
    qint32 m_cbMsgId;
    QString m_cbMsg;
    JsonArray m_uuids;
    QString m_taskUuid;
};

#endif // DELSTRUCTTASKADDRRUNNABLE_H
