#ifndef SERIALPOOL_H
#define SERIALPOOL_H

#include "netlib_global.h"
#include "serial/serialmanager.h"
#include "serial/core/serialdatagramutil.h"
#include "base.h"

class  NETLIBSHARED_EXPORT SerialPool : public QObject
{
    Q_OBJECT
public:
    SerialPool(QObject *parent = 0);
    ~SerialPool();
signals:
    void evt_error(const QString &errMsg);
    void evt_connectCom();
    void evt_disconnectCom();
    void evt_write(const QByteArray &data);
    void evt_read(SerialDataGramInfo *gram);
public slots:
    void on_error(const QString &errMsg);
    void on_read(SerialDataGramInfo *gram);
public:
    void connectCom();
    void disconnectCom();
    void write(const QByteArray &writeData);
private:
    void readConf();
private:
    SerialMeta* m_serialMeta;
    SerialManager* m_serialManager;
};

#endif // SERIALPOOL_H
