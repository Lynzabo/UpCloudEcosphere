#ifndef AUTASKNODERUNNABLE_H
#define AUTASKNODERUNNABLE_H
#include <QtCore>
#include <QObject>
#include"duplex.h"
#include "baseiremote.h"
#include "unstructoperairemoteui_global.h"
#include "base.h"
#include "avro.h"

class UNSTRUCTOPERAIREMOTEUISHARED_EXPORT AddUnstructTaskNodeServlet : public QRunnable
{
public:
    AddUnstructTaskNodeServlet(QObject* object = 0);
protected:
    void run();
private:
    QObject * m_object;
    qint32  m_cbMsgId;
    QString  m_cbMsg;

};

#endif // AUTASKNODERUNNABLE_H
