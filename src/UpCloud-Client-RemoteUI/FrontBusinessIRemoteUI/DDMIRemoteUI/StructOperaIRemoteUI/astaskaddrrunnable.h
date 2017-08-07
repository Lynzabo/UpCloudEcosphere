#ifndef ADDSTRUCTTASKADDRRUNNABLE_H
#define ADDSTRUCTTASKADDRRUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "structoperairemoteui_global.h"
#include "baseiremote.h"
using QtJson::JsonArray;

class STRUCTOPERAIREMOTEUISHARED_EXPORT AddStructTaskAddrRunnable : public QRunnable
{
public:
    AddStructTaskAddrRunnable(QObject* object = 0);
protected:
    void run();
public:
    void setAddCondition(const QStringList &uuids,const QString &taskuuid,const QStringList &groupDes);
private:
    QObject* m_object;
    qint32 m_cbMsgId;
    QString m_cbMsg;
    QStringList m_uuids;
    QString m_taskUuid;
    QStringList m_groupDes;
};

#endif // ADDSTRUCTTASKADDRRUNNABLE_H
