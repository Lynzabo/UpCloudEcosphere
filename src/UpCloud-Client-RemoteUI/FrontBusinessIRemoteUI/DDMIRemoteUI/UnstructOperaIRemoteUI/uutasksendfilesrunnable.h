#ifndef UPDATEUNSTRUCTTASKSENDFILESRUNNABLE_H
#define UPDATEUNSTRUCTTASKSENDFILESRUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "unstructoperairemoteui_global.h"
#include "baseiremote.h"
#include "../../../../UpCloud-Service-Center/BusinessIServer/UnstructIServer/bean/csrusendfiles.h"

class UNSTRUCTOPERAIREMOTEUISHARED_EXPORT UpdateUnstructTaskSendFilesRunnable : public QRunnable
{
public:
    UpdateUnstructTaskSendFilesRunnable(QObject* object = 0);
protected:
    void run();
public:
    void setUpdateState(const QStringList &Uuids,const QString &taskuuid,const quint8 state);
private:
    QObject* m_object;
    qint32 m_cbMsgId;
    QString m_cbMsg;
    QStringList m_uuids;
    QString m_taskUuid;
    quint8 m_state;
};

#endif // UPDATEUNSTRUCTTASKSENDFILESRUNNABLE_H
