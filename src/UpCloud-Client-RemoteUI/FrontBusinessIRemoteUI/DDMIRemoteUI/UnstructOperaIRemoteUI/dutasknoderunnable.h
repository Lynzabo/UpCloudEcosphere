#ifndef DELUNSTRUCTTASKNODESERVLET_H
#define DELUNSTRUCTTASKNODESERVLET_H
#include <QtCore>
#include <QObject>
#include"duplex.h"
#include "baseiremote.h"
#include "unstructoperairemoteui_global.h"
#include "base.h"
#include "avro.h"
using QtJson::JsonArray;
class UNSTRUCTOPERAIREMOTEUISHARED_EXPORT DelUnstructTaskAddrRunnable : public QRunnable
{
public:
    DelUnstructTaskAddrRunnable(QObject* object = 0);
protected:
    void run();
public:
    void setAddrUuids(const JsonArray &json,const QString &taskuuid);
private:
    QObject* m_object;
    qint32 m_cbMsgId;
    QString m_cbMsg;
    JsonArray m_uuids;
    QString m_taskUuid;

};

#endif // DELUNSTRUCTTASKNODESERVLET_H
