#ifndef UPDATEDICTRUNNABLE_H
#define UPDATEDICTRUNNABLE_H
#include <QtCore>
#include "duplex.h"
#include "base.h"
#include "avro.h"
#include "baseiremote.h"
#include "basaloperairemoteui_global.h"
#include <QList>
#include "../../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/csdict.h"

class BASALOPERAIREMOTEUISHARED_EXPORT UpdateDictRunnable : public QRunnable
{
public:
    UpdateDictRunnable(QObject* object = 0);
    void setUpdateList(QList<CsDict> dictList);
protected:
    void run();
private:
    QObject* m_object;
    qint32 m_cbMsgId;
    QString m_cbMsg;
    QList<CsDict> m_dictList;
};

#endif // UPDATEDICTRUNNABLE_H
