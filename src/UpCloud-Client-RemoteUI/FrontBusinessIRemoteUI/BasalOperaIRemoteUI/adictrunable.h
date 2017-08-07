#ifndef ADDDICTRUNABLE_H
#define ADDDICTRUNABLE_H
#include <QtCore>
#include "duplex.h"
#include "base.h"
#include "avro.h"
#include "baseiremote.h"
#include "basaloperairemoteui_global.h"
#include "../../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/csdict.h"
#include <QList>
class BASALOPERAIREMOTEUISHARED_EXPORT AddDictRunable : public QRunnable
{
public:
    AddDictRunable(QObject* object = 0);
    void setDictInfo(const CsDict &dict);
protected:
    void run();
private:
    QObject* m_object;
    qint32 m_cbMsgId;
    QString m_cbMsg;
    CsDict m_dict;
};

#endif // ADDDICTRUNABLE_H
