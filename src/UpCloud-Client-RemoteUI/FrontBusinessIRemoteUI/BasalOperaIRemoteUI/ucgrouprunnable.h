#ifndef UPDATECLIENTGROUP_H
#define UPDATECLIENTGROUP_H
#include <QtCore>
#include "duplex.h"
#include "avro.h"
#include "base.h"
#include "basaloperairemoteui_global.h"
#include "baseiremote.h"

class BASALOPERAIREMOTEUISHARED_EXPORT UpdateClientGroupRunnable : public QRunnable
{
public:
    UpdateClientGroupRunnable(QObject* object = 0);
    void setGroupInfo(const QVariantMap &params);
protected:
    void run();
private:
    QObject* m_object;
    qint32  m_cbMsgId;
    QString  m_cbMsg;
    QVariantMap m_params;
};

#endif // UPDATECLIENTGROUP_H
