#ifndef DELCLIENTGROUPASSOCRUNNABLE_H
#define DELCLIENTGROUPASSOCRUNNABLE_H
#include <QtCore>
#include "avro.h"
#include "duplex.h"
#include "basaloperairemoteui_global.h"
#include "base.h"
#include "baseiremote.h"
using QtJson::JsonArray;

class BASALOPERAIREMOTEUISHARED_EXPORT DelClientGroupAssocRunnable : public QRunnable
{
public:
    DelClientGroupAssocRunnable(QObject* object = 0);
    void setDelCondition(const QVariantMap& params);
protected:
    void run();
private:
    QObject* m_object;
    qint32  m_cbMsgId;
    QString  m_cbMsg;
    QVariantMap m_params;
};

#endif // DELCLIENTGROUPASSOCRUNNABLE_H
