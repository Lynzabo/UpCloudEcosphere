#ifndef SERIALCONF_H
#define SERIALCONF_H

#include <QSettings>
#include "QSerialPort"
class  SerialConf : public QObject
{
public:
    SerialConf(QObject* parent = 0);

    void getComPort(QString &comPort);
    void getBaudRate(QSerialPort::BaudRate &baudRate);
    void getDataBits(QSerialPort::DataBits &dataBits);
    void getParityBits(QSerialPort::Parity &parityBits);
    void getStopBits(QSerialPort::StopBits &stopBits);
    void getFlowControl(QSerialPort::FlowControl &flowControl);
private:
    QSettings* m_set;
};

#endif // SERIALCONF_H
