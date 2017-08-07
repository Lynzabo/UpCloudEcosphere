#ifndef UPDATECLIENTGROUPASSOCRUNNABLE_H
#define UPDATECLIENTGROUPASSOCRUNNABLE_H
#include <QtCore>
#include "avro.h"
#include "duplex.h"
#include "basaloperairemoteui_global.h"
#include "base.h"
#include "baseiremote.h"
using QtJson::JsonArray;

class BASALOPERAIREMOTEUISHARED_EXPORT UpdateClientGroupAssocRunnable : public QRunnable
{
public:
    UpdateClientGroupAssocRunnable(QObject* object = 0);
    void setGroupAssocInfo(const QVariantMap &params);
protected:
    void run();
private:
    QObject* m_object;
    qint32  m_cbMsgId;
    QString  m_cbMsg;
    QVariantMap m_params;
};

#endif // UPDATECLIENTGROUPASSOCRUNNABLE_H
