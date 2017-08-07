#ifndef ITEMSTRUCTTASKRUNNABLE_H
#define ITEMSTRUCTTASKRUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "structoperairemoteui_global.h"
#include "baseiremote.h"

class STRUCTOPERAIREMOTEUISHARED_EXPORT ItemStructTaskRunnable : public QRunnable
{
public:
    ItemStructTaskRunnable(QObject* object = 0);
protected:
    void run();
public:
    void setTaskUuid(const QVariantMap &map);
private:
    QObject* m_object;
    qint32 m_cbMsgId;
    QString m_cbMsg;
    QVariantMap m_map;
};

#endif // ITEMSTRUCTTASKRUNNABLE_H
