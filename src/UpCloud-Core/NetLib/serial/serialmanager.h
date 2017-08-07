#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H

#include "netlib_global.h"
#include "core/serialmeta.h"
#include "core/serialdatagraminfo.h"
#include "core/serialdatagramutil.h"
#include <QSerialPort>

class  NETLIBSHARED_EXPORT SerialManager : public QThread
{
    Q_OBJECT
public:
    SerialManager(QObject *parent = 0,SerialMeta *_serialMeta = 0);
    ~SerialManager();
signals:
    void evt_error(const QString &errMsg);

    void evt_restructure_datagram(const QByteArray &datas);
    void evt_read(SerialDataGramInfo *gram);

private slots:
    //err
    void on_error(QSerialPort::SerialPortError errMsg);
    //conn
    void on_connectCom();
    void on_disconnectCom();
    //write
    void on_writeData(const QByteArray &data);
    //read
    void on_new_data_recieved();
    void on_restructure_datagram(const QByteArray &datas);
private:
    SerialMeta* m_serialMeta;
    QSerialPort* m_serialPort;
    //写入服务器数据上锁
    QMutex *lock_write;
    //即要传输报文队列
    QQueue<QByteArray> gramQueue;
    //要重组的数据流
    QQueue<QByteArray> restructQueue;
    //重组数据流上锁
    QMutex *lock_restruct;
    QByteArray cachedArray;
    SerialDataGramInfo *gramInfo;
    quint8 currentState;//0 begin 1 type 2 time 3 datalength 4 msg 5 end
};

#endif // SERIALMANAGER_H
