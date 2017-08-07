#ifndef LISTSTRUCTADDRRUNNABLE_H
#define LISTSTRUCTADDRRUNNABLE_H
#include <QtCore>
#include "base.h"
#include "erm.h"
#include "avro.h"
#include "duplex.h"
#include "structoperairemoteui_global.h"
#include "baseiremote.h"

class STRUCTOPERAIREMOTEUISHARED_EXPORT ListStructAddrRunnable : public QRunnable
{
public:
    ListStructAddrRunnable(QObject* object = 0);
protected:
    void run();
public:
    void setTaskUuid(const QString &taskuuid);

    void setFilterPage(Page* page);
private:
    QObject* m_object;
    qint32 m_cbMsgId;
    QString m_cbMsg;
    QString m_taskUuid;
    Page* m_page;
};

#endif // LISTSTRUCTADDRRUNNABLE_H
