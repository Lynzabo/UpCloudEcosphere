#ifndef DELSTRUCTTASKFILERUNNABLE_H
#define DELSTRUCTTASKFILERUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "structoperairemoteui_global.h"
#include "baseiremote.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrssendfiles.h"
#include <QList>

using QtJson::JsonArray;

class STRUCTOPERAIREMOTEUISHARED_EXPORT DelStructTaskFileRunnable : public QRunnable
{
public:
    DelStructTaskFileRunnable(QObject* object = 0);
protected:
    void run();
public:
    void setFileInfo(const QString &taskuuid,const JsonArray &uuids);
private:
    QObject* m_object;
    qint32 m_cbMsgId;
    QString m_cbMsg;
    JsonArray m_uuids;
    QString m_taskUuid;
};

#endif // DELSTRUCTTASKFILERUNNABLE_H
