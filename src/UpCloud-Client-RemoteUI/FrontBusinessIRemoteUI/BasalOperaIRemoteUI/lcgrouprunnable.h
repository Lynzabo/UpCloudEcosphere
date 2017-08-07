#ifndef LISTCLIENTGROUPRUNNABLE_H
#define LISTCLIENTGROUPRUNNABLE_H
#include <QtCore>
#include "avro.h"
#include "duplex.h"
#include "basaloperairemoteui_global.h"
#include "base.h"
#include "baseiremote.h"
using QtJson::JsonArray;

class BASALOPERAIREMOTEUISHARED_EXPORT ListClientGroupRunnable : public QRunnable
{
public:
    ListClientGroupRunnable(QObject* object = 0);
    //默认list最后一位是分页的批次
    void setGroupInfo(const QStringList &list,const quint32 page);
protected:
    void run();
private:
    QObject* m_object;
    qint32  m_cbMsgId;
    QString  m_cbMsg;
    QStringList m_supUuids;
    quint32 m_page;
};

#endif // LISTCLIENTGROUPRUNNABLE_H
