#ifndef DELDICTRUNNABLE_H
#define DELDICTRUNNABLE_H
#include <QtCore>
#include "duplex.h"
#include "base.h"
#include "avro.h"
#include "baseiremote.h"
#include "basaloperairemoteui_global.h"
#include <QList>

class BASALOPERAIREMOTEUISHARED_EXPORT DelDictRunnable : public QRunnable
{
public:
    DelDictRunnable(QObject* object = 0);
    void setDictList(const QStringList &uuids);
protected:
    void run();
private:
    QObject* m_object;
    qint32 m_cbMsgId;
    QString m_cbMsg;
    QStringList m_uuids;
};

#endif // DELDICTRUNNABLE_H
