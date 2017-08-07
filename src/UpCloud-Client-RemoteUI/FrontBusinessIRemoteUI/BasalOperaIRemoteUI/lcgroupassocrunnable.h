#ifndef LISTCLIENTGROUPASSOCRUNNABLE_H
#define LISTCLIENTGROUPASSOCRUNNABLE_H
#include <QtCore>
#include "avro.h"
#include "duplex.h"
#include "basaloperairemoteui_global.h"
#include "base.h"
#include "baseiremote.h"
using QtJson::JsonArray;

class BASALOPERAIREMOTEUISHARED_EXPORT ListClientGroupAssocRunnable : public QRunnable
{
public:
    ListClientGroupAssocRunnable(QObject* object = 0 );
    void setGroupAssocUuid(const QString & supuuid,const quint32 page = 0);
protected:
    void run();
private:
    QObject* m_object;
    qint32  m_cbMsgId;
    QString  m_cbMsg;
    QString m_supuuid;
    quint32 m_page;
};

#endif // LISTCLIENTGROUPASSOCRUNNABLE_H
