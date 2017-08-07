#ifndef ASTASKRUNNABLE_H
#define ASTASKRUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "structoperairemoteui_global.h"
#include "baseiremote.h"
#include "../../UpCloud-Service-Center/BusinessIServer/StructIServer/bean/csrstask.h"

#include "../../../../UpCloud-Service-Center/FrontBusinessIServer/DDMIServer/StructOperaIServer/util/structutil.h"
class STRUCTOPERAIREMOTEUISHARED_EXPORT AddStructTaskRunnable : public QRunnable
{
public:
    AddStructTaskRunnable(QObject *object = 0);
    void setAddCondition(const CsRStructTask &task,const QList<CsRStructSendAddr> &addrInfoList,
                         const QList<CsRStructSendFiles> &fileInfoList,
                         const QList<CsRStructSendStatus> &statusInfoList);
protected:
    void run();
private:
    QObject *m_object;
    //消息ID
    qint32 cbMsgId;
    //消息内容
    QString cbMsg;
    CsRStructTask m_task;
    QList<CsRStructSendAddr> m_addrInfoList;
    QList<CsRStructSendFiles>  m_fileInfoList;
    QList<CsRStructSendStatus> m_statusInfoList;
};
#endif // ASTASKRUNNABLE_H
