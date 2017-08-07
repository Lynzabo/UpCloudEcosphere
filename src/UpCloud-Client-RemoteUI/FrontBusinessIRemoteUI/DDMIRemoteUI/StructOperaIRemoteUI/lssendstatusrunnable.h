#ifndef LISTSTRUCTSENDSTATUSRUNNABLE_H
#define LISTSTRUCTSENDSTATUSRUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "erm.h"
#include "duplex.h"
#include "structoperairemoteui_global.h"
#include "baseiremote.h"

class STRUCTOPERAIREMOTEUISHARED_EXPORT ListStructSendStatusRunnable : public QRunnable
{
public:
    ListStructSendStatusRunnable(QObject* object = 0);
protected:
    void run();
public:
    //设置要查询的节点服务器固定码
    void setNodeUuid(const QString &taskUuid,const QString &clientUuid);
    //设置要查询的文件名
    void setFileName(const QString &taskUuid,const QString &fileName);
    //设置分页信息
    void setFilterPage(Page* page);
private:
    QObject* m_object;
    qint32 m_cbMsgId;
    QString m_cbMsg;
    QString m_clientUuid;
    QString m_fileName;
    QString m_taskUuid;

    Page* m_page;
};

#endif // LISTSTRUCTSENDSTATUSRUNNABLE_H
