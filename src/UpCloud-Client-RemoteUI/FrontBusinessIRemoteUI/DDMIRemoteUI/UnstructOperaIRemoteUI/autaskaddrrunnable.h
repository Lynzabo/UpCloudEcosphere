#ifndef ADDUNSTRUCTTASKADDRRUNNABLE_H
#define ADDUNSTRUCTTASKADDRRUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "unstructoperairemoteui_global.h"
#include "baseiremote.h"
using QtJson::JsonArray;

class UNSTRUCTOPERAIREMOTEUISHARED_EXPORT AddUnstructTaskAddrRunnable : public QRunnable
{
public:
    AddUnstructTaskAddrRunnable(QObject *object = 0);
protected:
    void run();
public:
    void setAddCondition(const QStringList &clientUuids,const QString &taskuuid,const QStringList &groupDes);
private:
    QObject* m_object;
    qint32 m_cbMsgId;
    QString m_cbMsg;
    QStringList m_uuids;
    QString m_taskUuid;
    QStringList m_groupDes;
};

#endif // ADDUNSTRUCTTASKADDRRUNNABLE_H
