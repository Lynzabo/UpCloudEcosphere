#ifndef CHAIN_H
#define CHAIN_H
#include <QtCore>
#include <QTcpSocket>
#include "transmsg.h"
#include "actionlib_global.h"
#include "request/abstractrequest.h"
#include "response/abstractresponse.h"
class ACTIONLIBSHARED_EXPORT Chain : public QObject
{
    Q_OBJECT
public:
    explicit Chain(QObject *parent = 0);
    virtual void invoke(RequestContext *request = 0,ResponseContext *response = 0, DataGramInfo *gram = 0) = 0;
signals:

public slots:
};

#endif // CHAIN_H
