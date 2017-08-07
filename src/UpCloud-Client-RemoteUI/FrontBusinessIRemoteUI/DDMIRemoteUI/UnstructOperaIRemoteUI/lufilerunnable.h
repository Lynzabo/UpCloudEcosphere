#ifndef LISTUNSTRUCTFILERUNNABLE_H
#define LISTUNSTRUCTFILERUNNABLE_H
#include <QtCore>
#include "base.h"
#include "erm.h"
#include "avro.h"
#include "duplex.h"
#include "unstructoperairemoteui_global.h"
#include "baseiremote.h"
#include "../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendfiles.h"

class UNSTRUCTOPERAIREMOTEUISHARED_EXPORT ListUnstructFileRunnable : public QRunnable
{
public:
    ListUnstructFileRunnable(QObject *object = 0);
protected:
    void run();
public:
    void setTaskUUID(const QString &taskuuid);

    void setFilterPage(Page* page);
private:
    QObject* m_object;
    qint32 m_cbMsgId;
    QString m_cbMsg;
    QString m_taskUuid;
    Page* m_page;
};

#endif // LISTUNSTRUCTFILERUNNABLE_H
