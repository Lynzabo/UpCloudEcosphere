#ifndef ADDCSCLIENTGROUP_H
#define ADDCSCLIENTGROUP_H
#include <QtCore>
#include "avro.h"
#include "duplex.h"
#include "basaloperairemoteui_global.h"
#include "base.h"
#include "baseiremote.h"

class BASALOPERAIREMOTEUISHARED_EXPORT AddCsClientGroupRunnable : public QRunnable
{
public:
    AddCsClientGroupRunnable(QObject* object = 0);
    void setGroupInfo(const QVariantMap &params);
protected:
    void run();
private:
    QObject* m_object;
    qint32  m_cbMsgId;
    QString  m_cbMsg;
    QVariantMap m_params;

};

#endif // ADDCSCLIENTGROUP_H
