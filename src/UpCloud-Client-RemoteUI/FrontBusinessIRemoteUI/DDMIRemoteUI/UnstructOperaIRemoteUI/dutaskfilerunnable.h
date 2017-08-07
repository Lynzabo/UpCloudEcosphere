#ifndef DELUNSTRUCTTASKFILESERVLET_H
#define DELUNSTRUCTTASKFILESERVLET_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "unstructoperairemoteui_global.h"
#include "baseiremote.h"
#include "../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendfiles.h"

using QtJson::JsonArray;
class UNSTRUCTOPERAIREMOTEUISHARED_EXPORT DelUnstructTaskFileRunnable:public QRunnable
{
public:
    DelUnstructTaskFileRunnable(QObject *object = 0);
protected:
    void run();
public:
    void setFileUuids(const QString &taskuuid, const JsonArray &uuids);
private:
    QObject* m_object;
    qint32 m_cbMsgId;
    QString m_cbMsg;
    JsonArray m_uuids;
    QString m_taskUuid;
};

#endif // DELUNSTRUCTTASKFILESERVLET_H
