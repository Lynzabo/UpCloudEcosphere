#ifndef LISTSTRUCTFILERUNNABLE_H
#define LISTSTRUCTFILERUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "erm.h"
#include "duplex.h"
#include "structoperairemoteui_global.h"
#include "baseiremote.h"


class STRUCTOPERAIREMOTEUISHARED_EXPORT ListStructFileRunnable : public QRunnable
{
public:
    ListStructFileRunnable(QObject* object = 0);
protected:
    void run();
public:
    void setListCondition(const QString &taskuuid);

    void setFilterPage(Page* page);
private:
    QObject* m_object;
    qint32 m_cbMsgId;
    QString m_cbMsg;
    QString m_taskUuid;

    Page* m_page;
};

#endif // LISTSTRUCTFILERUNNABLE_H
