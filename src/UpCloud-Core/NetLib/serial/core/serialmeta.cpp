#include "serialmeta.h"

SerialMeta::Builder::Builder()
{
    serialport = new SerialMeta;
}

SerialMeta::Builder::Builder(const QString &comPort, const QSerialPort::BaudRate &baudRate, const QSerialPort::DataBits &dataBits, const QSerialPort::Parity &parityBits, const QSerialPort::StopBits &stopBits, const QSerialPort::FlowControl &flowControl)
{
  serialport = new SerialMeta;
  serialport->comPort = comPort;
  serialport->baudRate = baudRate;
  serialport->dataBits = dataBits;
  serialport->parityBits =  parityBits;
  serialport->stopBits = stopBits;
  serialport->flowControl = flowControl;

}
SerialMeta::Builder::~Builder()
{
    delete serialport;
}

SerialMeta::Builder *SerialMeta::Builder::setComPort(const QString &comPort)
{
    serialport->comPort = comPort;
    return this;
}

SerialMeta::Builder *SerialMeta::Builder::setBaudRate(const QSerialPort::BaudRate &baudRate)
{
    serialport->baudRate = baudRate;
    return this;
}

SerialMeta::Builder *SerialMeta::Builder::setDataBits(const QSerialPort::DataBits &dataBits)
{
    serialport->dataBits = dataBits;
    return this;
}

SerialMeta::Builder *SerialMeta::Builder::setParityBits(const QSerialPort::Parity &parityBits)
{
    serialport->parityBits =  parityBits;
    return this;
}

SerialMeta::Builder *SerialMeta::Builder::setStopBits(const QSerialPort::StopBits &stopBits)
{
    serialport->stopBits = stopBits;
    return this;
}

SerialMeta::Builder *SerialMeta::Builder::setFlowControl(const QSerialPort::FlowControl &flowControl)
{
    serialport->flowControl = flowControl;
    return this;
}

SerialMeta *SerialMeta::Builder::build()
{
    return serialport;
}


QString SerialMeta::getComPort() const
{
    return comPort;
}

QSerialPort::BaudRate SerialMeta::getBaudRate() const
{
    return baudRate;
}

QSerialPort::DataBits SerialMeta::getDataBits() const
{
    return dataBits;
}

QSerialPort::Parity SerialMeta::getParityBits() const
{
    return parityBits;
}

QSerialPort::StopBits SerialMeta::getStopBits() const
{
    return stopBits;
}

QSerialPort::FlowControl SerialMeta::getFlowControl() const
{
    return flowControl;
}


