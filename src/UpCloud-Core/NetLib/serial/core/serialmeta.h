#ifndef SERIALMETA_H
#define SERIALMETA_H

#include <QtCore>

#include <QtSerialPort/QSerialPort>

class  SerialMeta
{
public:
    SerialMeta(){}
    ~SerialMeta(){}
public:
    class  Builder
    {
    public:
        Builder();
        Builder(const QString &comPort,
                const QSerialPort::BaudRate &baudRate,
                const QSerialPort::DataBits &dataBits,
                const QSerialPort::Parity &parityBits,
                const QSerialPort::StopBits &stopBits,
                const QSerialPort::FlowControl &flowControl);
        ~Builder();
    public:
        Builder*  setComPort(const QString &comPort);
        Builder*  setBaudRate(const QSerialPort::BaudRate &baudRate);
        Builder*  setDataBits(const QSerialPort::DataBits &dataBits);
        Builder*  setParityBits(const QSerialPort::Parity &parityBits);
        Builder*  setStopBits(const QSerialPort::StopBits &stopBits);
        Builder*  setFlowControl(const QSerialPort::FlowControl &flowControl);
        SerialMeta*  build();
    private:
        SerialMeta* serialport;
    };
public:
    QString getComPort() const;
    QSerialPort::BaudRate getBaudRate() const;
    QSerialPort::DataBits getDataBits() const;
    QSerialPort::Parity getParityBits() const;
    QSerialPort::StopBits getStopBits() const;
    QSerialPort::FlowControl getFlowControl() const;
private:
    //串口号
    QString comPort;
    //波特率
    QSerialPort::BaudRate baudRate;
    //数据位
    QSerialPort::DataBits dataBits;
    //校验位
    QSerialPort::Parity parityBits;
    //停止位
    QSerialPort::StopBits stopBits;
    //流控
    QSerialPort::FlowControl flowControl;
};

#endif // SERIALMETA_H

