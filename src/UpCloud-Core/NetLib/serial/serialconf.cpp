#include "serialconf.h"
#include "base.h"
SerialConf::SerialConf(QObject *parent): QObject(parent)
{
    //TODO修改地址
    m_set = new QSettings("c:/NodeServer-serialport.conf", QSettings::IniFormat);
}

void SerialConf::getComPort(QString &comPort)
{
    comPort = "COM" + m_set->value("upCloud.serialport.comPort", 3).toString();
}

void SerialConf::getBaudRate(QSerialPort::BaudRate &baudRate)
{
    quint32 rate = m_set->value("upCloud.serialport.baudRate", 115200).toUInt();    
    switch (rate)
    {
        case 1200:
            baudRate = QSerialPort::Baud1200;
            break;
        case 2400:
            baudRate = QSerialPort::Baud2400;
            break;
        case 4800:
            baudRate = QSerialPort::Baud4800;
            break;
        case 9600:
            baudRate = QSerialPort::Baud9600;
            break;
        case 19200:
            baudRate = QSerialPort::Baud19200;
            break;
        case 38400:
            baudRate = QSerialPort::Baud38400;
            break;
        case 57600:
            baudRate = QSerialPort::Baud57600;
            break;
        case 115200:
            baudRate = QSerialPort::Baud115200;
            break;
    }
}

void SerialConf::getDataBits(QSerialPort::DataBits &dataBits)
{
    quint8 date = (quint8)m_set->value("upCloud.serialport.dataBits", 8).toUInt();
    switch (date)
    {
        case 5:
            dataBits = QSerialPort::Data5;
            break;
        case 6:
            dataBits = QSerialPort::Data6;
            break;
        case 7:
            dataBits = QSerialPort::Data7;
            break;
        case 8:
            dataBits = QSerialPort::Data8;
            break;
    }
}

void SerialConf::getParityBits(QSerialPort::Parity &parityBits)
{
    QString parity = m_set->value("upCloud.serialport.parityBits", "No").toString();
    if(QString::compare(parity, "No", Qt::CaseInsensitive) == 0)
    {
        parityBits = QSerialPort::NoParity;
    }
    else if(QString::compare(parity, "Even", Qt::CaseInsensitive) == 0)
    {
        parityBits = QSerialPort::EvenParity;
    }
    else if(QString::compare(parity, "Odd", Qt::CaseInsensitive) == 0)
    {
        parityBits = QSerialPort::OddParity;
    }
    else if(QString::compare(parity, "Space", Qt::CaseInsensitive) == 0)
    {
        parityBits = QSerialPort::SpaceParity;
    }
    else if(QString::compare(parity, "Mark", Qt::CaseInsensitive) == 0)
    {
        parityBits = QSerialPort::MarkParity;
    }
}

void SerialConf::getStopBits(QSerialPort::StopBits &stopBits)
{
    float stop = m_set->value("upCloud.serialport.stopBits", 1).toFloat();
    if(stop == 1)
    {
        stopBits = QSerialPort::OneStop;
    }
    else if(stop == 1.5)
    {
        stopBits = QSerialPort::OneAndHalfStop;
    }
    else if(stop == 2)
    {
        stopBits = QSerialPort::TwoStop;
    }
}

void SerialConf::getFlowControl(QSerialPort::FlowControl &flowControl)
{
    QString flow = m_set->value("upCloud.serialport.flowControl", "No").toString();
    if(QString::compare(flow, "No", Qt::CaseInsensitive) == 0)
    {
        flowControl = QSerialPort::NoFlowControl;
    }
    else if(QString::compare(flow, "Hardware", Qt::CaseInsensitive) == 0)
    {
        flowControl = QSerialPort::HardwareControl;
    }
    else if(QString::compare(flow, "Software", Qt::CaseInsensitive) == 0)
    {
        flowControl = QSerialPort::SoftwareControl;
    }
}

