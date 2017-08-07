#ifndef ADDCLIENTGROUPASSOCRUNNABLE_H
#define ADDCLIENTGROUPASSOCRUNNABLE_H
#include <QtCore>
#include "avro.h"
#include "duplex.h"
#include "basaloperairemoteui_global.h"
#include "base.h"
#include "baseiremote.h"
using QtJson::JsonArray;
class BASALOPERAIREMOTEUISHARED_EXPORT AddClientGroupAssocRunnable : public QRunnable
{
public:
    AddClientGroupAssocRunnable(QObject* object = 0);
    void setAddCondition(const QStringList & nodes,const QVariantMap &params);
protected:

    void run();
private:
    QObject* m_object;
    qint32  m_cbMsgId;
    QString  m_cbMsg;
    QStringList m_node;
    QVariantMap m_params;
};

#endif // ADDCLIENTGROUPASSOCRUNNABLE_H
