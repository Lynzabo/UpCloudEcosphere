#include "serialmanager.h"
#include <QReadWriteLock>

SerialManager::SerialManager(QObject *parent,SerialMeta *_serialMeta) : QThread(parent)
{
    gramInfo = new SerialDataGramInfo;
    cachedArray.clear();
    lock_restruct = new QMutex;
    restructQueue.clear();
currentState = 0;//
    gramQueue.clear();
    lock_write = new QMutex;
    m_serialMeta = _serialMeta;
    m_serialPort = new QSerialPort;

    connect(m_serialPort, SIGNAL(error(QSerialPort::SerialPortError)),
            this, SLOT(on_error(QSerialPort::SerialPortError)));

    connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(on_new_data_recieved()));
    connect(this, SIGNAL(evt_restructure_datagram(QByteArray)), this, SLOT(on_restructure_datagram(QByteArray)));

}

SerialManager::~SerialManager()
{
    disconnect(m_serialPort, SIGNAL(error(QSerialPort::SerialPortError)),
            this, SLOT(on_error(QSerialPort::SerialPortError)));

    disconnect(m_serialPort, SIGNAL(readyRead()), this, SLOT(on_new_data_recieved()));
    disconnect(this, SIGNAL(evt_restructure_datagram(QByteArray)), this, SLOT(on_restructure_datagram(QByteArray)));
    m_serialMeta = NULL;
    delete m_serialPort;
    m_serialPort = NULL;
}

void SerialManager::on_connectCom()
{
    m_serialPort->setPortName(m_serialMeta->getComPort());
    m_serialPort->setBaudRate(m_serialMeta->getBaudRate());
    m_serialPort->setDataBits(m_serialMeta->getDataBits());
    m_serialPort->setParity(m_serialMeta->getParityBits());
    m_serialPort->setStopBits(m_serialMeta->getStopBits());
    m_serialPort->setFlowControl(m_serialMeta->getFlowControl());
    if(!m_serialPort->open(QIODevice::ReadWrite))
    {
        emit evt_error("错误：打开串口失败");
    }

}

void SerialManager::on_disconnectCom()
{
    if (m_serialPort->isOpen())
        m_serialPort->close();
}

void SerialManager::on_writeData(const QByteArray &data)
{
    m_serialPort->write(data);
    m_serialPort->flush();
    qDebug() << "-----write data:" << data.toHex();
}


void SerialManager::on_error(QSerialPort::SerialPortError errMsg)
{
    if(errMsg != QSerialPort::NoError)
    {
        QString err = m_serialPort->errorString();
        emit evt_error(err);
    }
}

void SerialManager::on_new_data_recieved()
{

    QSerialPort * port = qobject_cast<QSerialPort*>(sender());
    if (port)
    {
        QByteArray array = port->readAll();
        qDebug() << "-----read data:" << array.toHex();        
        if(array.size()>0)
        {
            emit
                evt_restructure_datagram(array);
        }
    }
}


void SerialManager::on_restructure_datagram(const QByteArray &datas)
{    
    //0 begin 1 type 2 time 3 datalength 4 msg 5 end
    //qDebug() <<"串口收到的数据：" << datas.toHex();

    restructQueue.enqueue(datas);
    lock_restruct->lock();
    //存放队列出队元素
    QByteArray datagram;
    datagram.clear();
    //第一次cachedArray肯定为空,以后可能不为空,如果不为空,存放的是上次出队列的数据
    if(cachedArray.size()>0)
    {
        datagram.append(cachedArray);
        cachedArray.clear();
    }
    if(restructQueue.size()>0)
    {
        datagram.append(restructQueue.dequeue());
    }

    /*
    //对于传输过来的不符合报文装帧标准,会在解析报文体的时候校验    
    if(gramInfo->begin==0)
    {
        goto beginRead;
    }
    else if(gramInfo->msgType==0)
    {
        goto msgTypeRead;
    }
    else if(gramInfo->timestamp==0)
    {
        goto timestampRead;
    }
    else if(gramInfo->dataLength==0)
    {
        goto dataLengthRead;
    }
    else if(gramInfo->message.isEmpty())
    {
        goto messageRead;
    }
    else if(gramInfo->end==0)
    {
        goto endRead;
    }
    */

    //对于传输过来的不符合报文装帧标准,会在解析报文体的时候校验
    if(currentState==0)
    {
        goto beginRead;
    }
    else if(currentState==1)
    {
        goto msgTypeRead;
    }
    else if(currentState==2)
    {
        goto timestampRead;
    }
    else if(currentState==3)
    {
        goto dataLengthRead;
    }
    else if(currentState == 4)
    {
        goto messageRead;
    }
    else if(currentState == 5)
    {
        goto endRead;
    }

    //从流中依次读取出来每个元数据,如果本次长度不够,从下次报文中读取
    //1.文件开始标记-->2字节
    beginRead:;     
    if(datagram.size()>=2)
    {
        //qDebug() <<"beginRead";       
        bool ok;
        QByteArray data = datagram.mid(0, 2);
        SerialDatagramUtil::reversalArray(data);
        gramInfo->begin = (quint16)(data.toHex().toUShort(&ok,16));
        datagram.remove(0, 2);
        currentState=1;
        goto msgTypeRead;
    }
    else
        goto extra;
    msgTypeRead:;    
    //2.报文类型-->1字节
    if(datagram.size()>=1)
    {
        //qDebug() <<"msgTypeRead";
        bool ok;
        gramInfo->msgType = (quint8)(datagram.mid(0, 1).toHex().toUShort(&ok,16));
        datagram.remove(0, 1);
        currentState=2;
        goto timestampRead;
    }
    else
        goto extra;
    timestampRead:;    
    //3.时间戳-->8字节
    if(datagram.size()>=8)
    {
        //qDebug() <<"timestampRead";
        bool ok;
//        gramInfo->timestamp = (quint64)(datagram.at(0)*1000000000000+datagram.at(1)*10000000000
//                                        +datagram.at(2)*100000000+datagram.at(3)*1000000
//                                        +datagram.at(4)*10000+datagram.at(5)*100
//                                        +datagram.at(6)*1+datagram.at(7)*0);


        QByteArray data = datagram.mid(0, 2);
        SerialDatagramUtil::reversalArray(data);
        QString year = QString::number(data.toHex().toUShort(&ok,16));
        QString month = QString::number(datagram.mid(2, 1).toHex().toUShort(&ok,16));
        if(month.size() == 1)
        {
            month = "0" + month;
        }
        QString day = QString::number(datagram.mid(3, 1).toHex().toUShort(&ok,16));
        if(day.size() == 1)
        {
            day = "0" + day;
        }
        QString hour = QString::number(datagram.mid(4, 1).toHex().toUShort(&ok,16));
        if(hour.size() == 1)
        {
            hour = "0" + hour;
        }
        QString minute = QString::number(datagram.mid(5, 1).toHex().toUShort(&ok,16));
        if(minute.size() == 1)
        {
            minute = "0" + minute;
        }
        QString second = QString::number(datagram.mid(6, 1).toHex().toUShort(&ok,16));
        if(second.size() == 1)
        {
            second = "0" + second;
        }
//        qDebug() << "&&&&&&&y= " << QString::number(data.toHex().toUShort(&ok,16));
//        qDebug() << "&&&&&&&m= " << QString::number(datagram.mid(2, 1).toHex().toUShort(&ok,16));
//        qDebug() << "&&&&&&&d= " << QString::number(datagram.mid(3, 1).toHex().toUShort(&ok,16));
//        qDebug() << "&&&&&&&h= " << QString::number(datagram.mid(4, 1).toHex().toUShort(&ok,16));
//        qDebug() << "&&&&&&&m= " << QString::number(datagram.mid(5, 1).toHex().toUShort(&ok,16));
//        qDebug() << "&&&&&&&s= " << QString::number(datagram.mid(6, 1).toHex().toUShort(&ok,16));
        QString time = "";
        time = year + month + day + hour +minute +second;

         gramInfo->timestamp = (quint64)(time.toLongLong());

        datagram.remove(0,8);
        currentState=3;
        goto dataLengthRead;
    }
    else
        goto extra;
    dataLengthRead:;    
    //4.报文体长度-->4字节
    if(datagram.size()>=4)
    {
       // qDebug() <<"dataLengthRead";
//        gramInfo->dataLength = (quint32)(datagram.at(0)*10000+datagram.at(1)*1000
//                                         +datagram.at(2)*100+datagram.at(3)*1);
        bool ok;
        QByteArray data = datagram.mid(0, 4);
        SerialDatagramUtil::reversalArray(data);
        gramInfo->dataLength = (quint32)(data.toHex().toUInt(&ok,16));
        datagram.remove(0, 4);
        currentState=4;
        goto messageRead;
    }
    else
        goto extra;
    messageRead:;    
    //5.报文体-->gramInfo->dataLength字节
    if(datagram.size()>= gramInfo->dataLength)
    {
        //qDebug() <<"messageRead";
        for(int i=0; i<gramInfo->dataLength; i++)
        {
            QString str = QString::number((quint8)(datagram.at(i)), 16);
            if(str.length() == 1)
            {
                str="0"+str;
            }
            gramInfo->message.append(str);
        }
        datagram.remove(0, gramInfo->dataLength);
        currentState=5;
        goto endRead;
    }
    else
        goto extra;
    endRead:;
    //6.文件结尾标示符-->2字节
    //根据Qt机制肯定会把当前7个填满,然后进第8个.只是循环次数不清楚,每个DataGramInfo元数据合不合法也不知道,这个在业务部分有处理.  
    if(datagram.size()>=2)
    {
        //qDebug() <<"endRead";
        bool ok;
        QByteArray data = datagram.mid(0, 2);
        SerialDatagramUtil::reversalArray(data);
        gramInfo->end = (quint16)(data.toHex().toUShort(&ok,16));
        datagram.remove(0, 2);
        currentState=0;
        emit evt_read(gramInfo);
        gramInfo->clear();
        goto extra;
    }
    else
        goto extra;
    extra:;
    //将本次未读的数据放到缓冲区域,等插入到下次数据流前面
    cachedArray.append(datagram);
    datagram.clear();
    lock_restruct->unlock();
    return;
}

