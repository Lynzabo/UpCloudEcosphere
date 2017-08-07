#ifndef LISTCLIENTEXTENDINFORUNNABLE_H
#define LISTCLIENTEXTENDINFORUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "baseiremote.h"
#include "basaloperairemoteui_global.h"

class BASALOPERAIREMOTEUISHARED_EXPORT ListClientExtendInfoRunnable : public QRunnable
{
public:
    ListClientExtendInfoRunnable(QObject* object = 0);
    void setExtendInfo(const QString &clientUuid);
protected:
    void run();
private:
    QObject* m_object;
    qint32 m_cbMsgId;
    QString m_cbMsg;
    QString m_clientUuid;
};

#endif // LISTCLIENTEXTENDINFORUNNABLE_H
