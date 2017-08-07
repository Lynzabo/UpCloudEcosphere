#ifndef ADDSCHEDULETASKADDRRUNABLE_H
#define ADDSCHEDULETASKADDRRUNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "scheduleoperairemoteui_global.h"
#include "baseiremote.h"

class SCHEDULEOPERAIREMOTEUISHARED_EXPORT AddScheduleTaskAddrRunable : public QRunnable
{
public:
    AddScheduleTaskAddrRunable(QObject* object = 0);
    void setAddrInfo(const QString &taskUuid, const QStringList &nodes, const QStringList &groupDes);
protected:
    void run();
private:
    qint32 m_cbMsgID;
    QString m_cbMsg;
    QObject* m_object;
    QString m_taskUuid;
    QStringList m_nodes;
    QStringList m_groupDes;
};

#endif // ADDSCHEDULETASKADDRRUNABLE_H
