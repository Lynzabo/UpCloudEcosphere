#include "serialdatagramutil.h"
#include "base.h"
using namespace Environment::Serial::DataType;
SerialDatagramUtil::SerialDatagramUtil()
{

}

void SerialDatagramUtil::packDatagram(quint8 msgType, QByteArray &datagram)
{
    QBuffer buffer(&datagram);
    buffer.open(QIODevice::WriteOnly);
    //输入
    QDataStream out(&buffer);
    out.setByteOrder(QDataStream::LittleEndian);
    out.setVersion(QDataStream::Qt_4_7);

    //1.文件开始标记-->2字节
    quint16 begin = 0xE1E2;
    out << begin;
    //2.报文类型-->1字节
    out <<msgType;
    //3.时间戳-->8字节
    QString time = QDateTime::currentDateTime().toString("yyyyMMddHHmmss");
    out << time.mid(0,4).toUShort();
    out << (quint8)time.mid(4,2).toUShort();
    out << (quint8)time.mid(6,2).toUShort();
    out << (quint8)time.mid(8,2).toUShort();
    out << (quint8)time.mid(10,2).toUShort();
    out << (quint8)time.mid(12,2).toUShort();
    out << (quint8)0;
    //4.报文体长度-->4字节
    if(msgType == GPS)
    {
        out << (quint32)0;
    }
    else if(msgType == TemHum)
    {
        out << (quint32)0;
    }
    else if(msgType == SyschronizedTime)
    {
        out << (quint32)8;
    }
    else if(msgType == MachineUUID)
    {
        out << (quint32)0;
    }
    else
    {
        out << (quint32)4;
    }
    //5.报文体
    if(msgType == SyschronizedTime)
    {
        QString time = QDateTime::currentDateTime().toString("yyyyMMddHHmmss");
        out << time.mid(0,4).toUShort();
        out << (quint8)time.mid(4,2).toUShort();
        out << (quint8)time.mid(6,2).toUShort();
        out << (quint8)time.mid(8,2).toUShort();
        out << (quint8)time.mid(10,2).toUShort();
        out << (quint8)time.mid(12,2).toUShort();
        out << (quint8)0;
    }

    //6.文件结尾标示符-->2字节
    quint16 end = 0xF3F4;
    out << end;

    buffer.close();
}

void SerialDatagramUtil::reversalArray(QByteArray &data)
{
    int size = data.size();

    QByteArray old;
    old.clear();
    for(int i=0; i<size; i++)
    {
        old.append(data.at(i));
    }

    data.clear();
    size--;
    for(int i=0; i<old.size(); i++, size--)
    {
        data.append(old.at(size));
    }
}

