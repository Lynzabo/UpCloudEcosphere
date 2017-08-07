#include "serialpool.h"
#include "serial/serialconf.h"
using namespace Environment::Serial;
SerialPool::SerialPool(QObject *parent): QObject(parent)
{
    this->readConf();
    m_serialManager = new SerialManager(this,m_serialMeta);
    connect(this, SIGNAL(evt_connectCom()), m_serialManager, SLOT(on_connectCom()));
    connect(this, SIGNAL(evt_disconnectCom()), m_serialManager, SLOT(on_disconnectCom()));
    connect(m_serialManager, SIGNAL(evt_error(QString)), this, SLOT(on_error(QString)));
    connect(m_serialManager, SIGNAL(evt_read(SerialDataGramInfo*)), this, SLOT(on_read(SerialDataGramInfo*)),Qt::DirectConnection);
    connect(this, SIGNAL(evt_write(QByteArray)), m_serialManager, SLOT(on_writeData(QByteArray)));
}

SerialPool::~SerialPool()
{
    disconnect(this, SIGNAL(evt_connectCom()), m_serialManager, SLOT(on_connectCom()));
    disconnect(this, SIGNAL(evt_disconnectCom()), m_serialManager, SLOT(on_disconnectCom()));
    disconnect(m_serialManager, SIGNAL(evt_error(QString)), this, SLOT(on_error(QString)));
    disconnect(m_serialManager, SIGNAL(evt_read(SerialDataGramInfo*)), this, SLOT(on_read(SerialDataGramInfo*)));
    disconnect(this, SIGNAL(evt_write(QByteArray)), m_serialManager, SLOT(on_writeData(QByteArray)));
    delete m_serialManager;
    m_serialManager  = NULL;
    delete m_serialMeta;
    m_serialMeta = NULL;
}

void SerialPool::on_error(const QString &errMsg)
{
    //处理错误信息
    qDebug() << errMsg;
    emit evt_error(errMsg);
}

void SerialPool::on_read(SerialDataGramInfo *gram)
{
    //处理读取出来的数据    
    //文件开始标记-->2字节
    quint16 begin = gram->begin;
    //报文类型-->1字节
    quint8 msgType = gram->msgType;
    //时间戳-->8字节
    quint64 timestamp = gram->timestamp;
    //报文体长度-->4字节
    quint32 dataLength = gram->dataLength;
    //报文体
    QString message = gram->message;
    //文件结尾标示符-->2字节
    quint16 end = gram->end;
    qDebug()<< "\n##begin = "<<begin;
    qDebug()<< "\n##msgType = "<<msgType;
    qDebug()<< "\n##timestamp = "<<timestamp;
    qDebug()<< "\n##dataLength = "<<dataLength;

    if(msgType == 1)
    {
        qDebug() << "\n------##message title[8] = "<<QByteArray::fromHex(message.mid(0, 16).toLocal8Bit()).data();
        qDebug() << "\n------##message time[8] = "<<QByteArray::fromHex(message.mid(16, 16).toLocal8Bit()).data();
        qDebug() << "\n------##message northdata[20] = "<<QByteArray::fromHex(message.mid(32, 40).toLocal8Bit()).data();
        qDebug() << "\n------##message north[2] = "<<QByteArray::fromHex(message.mid(72, 4).toLocal8Bit()).data();
        qDebug() << "\n------##message eastdata[20] = "<<QByteArray::fromHex(message.mid(76, 40).toLocal8Bit()).data();
        qDebug() << "\n------##message east[2] = "<<QByteArray::fromHex(message.mid(116, 4).toLocal8Bit()).data();
        qDebug() << "\n------##message satellitenum[3] = "<<QByteArray::fromHex(message.mid(120, 6).toLocal8Bit()).data();
        qDebug() << "\n------##message error[10] = "<<QByteArray::fromHex(message.mid(126, 20).toLocal8Bit()).data();

    }
    else if(msgType == 2)
    {
        bool ok;
        QString shidu=message.mid(2,2)+message.mid(0,2);
        QString wendu=message.mid(6,2)+message.mid(4,2);
//        qDebug()<< "\n------##message shidu = "<<message.mid(0, 4).toUShort(&ok, 16);
//        qDebug()<< "\n------##message wendu = "<<message.mid(4, 4).toUShort(&ok, 16);
          qDebug()<< "\n------##message shidu = "<<shidu.toUShort(&ok, 16);
          qDebug()<< "\n------##message wendu = "<<wendu.toUShort(&ok, 16);
    }
    else if(msgType == 3)
    {
        QByteArray datagram;
        SerialDatagramUtil::packDatagram(DataType::SyschronizedTime, datagram);
        this->write(datagram);
    }
    else if(msgType == 4)
    {
        qDebug()<< "\n------##message machinUUID = "<<message;
    }

    qDebug()<< "\n##end = "<<end;
    emit evt_read(gram);
}

void SerialPool::write(const QByteArray &writeData)
{
    emit evt_write(writeData);
}

void SerialPool::connectCom()
{
    emit evt_connectCom();
}

void SerialPool::disconnectCom()
{
    emit evt_disconnectCom();
}

void SerialPool::readConf()
{
//    //串口号
//    QString comPort = "COM3";
//    //波特率
//    QSerialPort::BaudRate baudRate = QSerialPort::Baud115200;
//    //数据位
//    QSerialPort::DataBits dataBits = QSerialPort::Data8;
//    //校验位
//    QSerialPort::Parity parityBits = QSerialPort::NoParity;
//    //停止位
//    QSerialPort::StopBits stopBits = QSerialPort::OneStop;
//    //流控
//    QSerialPort::FlowControl flowControl = QSerialPort::NoFlowControl;

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

    SerialConf conf;
    conf.getComPort(comPort);
    conf.getBaudRate(baudRate);
    conf.getDataBits(dataBits);
    conf.getParityBits(parityBits);
    conf.getStopBits(stopBits);
    conf.getFlowControl(flowControl);

    qDebug() << "@@comPort="<<comPort ;
    qDebug() << "@@baudRate="<<baudRate ;
    qDebug() << "@@dataBits="<<dataBits ;
    qDebug() << "@@parityBits="<<parityBits ;
    qDebug() << "@@stopBits="<<stopBits ;
    qDebug() << "@@flowControl="<<flowControl ;

    SerialMeta::Builder *builder = new SerialMeta::Builder;
    m_serialMeta = (SerialMeta *)builder->setComPort(comPort)
            ->setBaudRate(baudRate)
            ->setDataBits(dataBits)
            ->setParityBits(parityBits)
            ->setStopBits(stopBits)
            ->setFlowControl(flowControl)
            ->build();
}



