#include "tcpsocket.h"
#include <QMutex>
TcpSocket::TcpSocket(QObject *parent,int blockSize)
    : QTcpSocket(parent),
      blockSize(blockSize),m_uuid("")
{
    connect(this, SIGNAL(bytesWritten(qint64)), this, SLOT(some_data_sended(qint64)));
}

TcpSocket::~TcpSocket()
{

}
QString TcpSocket::uuid() const
{
    return m_uuid;
}

void TcpSocket::setUuid(const QString &uuid)
{
    m_uuid = uuid;
}


void TcpSocket::some_data_sended(qint64 wsended)
{
    while (m_buffer_sending.empty()==false)
    {
        QByteArray & arraySending = *m_buffer_sending.begin();
        qint64 & currentOffset = *m_buffer_sending_offset.begin();
        qint64 nTotalBytes = arraySending.size();
        assert(nTotalBytes>=currentOffset);
        qint64 nBytesWritten = write(arraySending.constData()+currentOffset,qMin((int)(nTotalBytes-currentOffset),blockSize));
        currentOffset += nBytesWritten;
        if (currentOffset>=nTotalBytes)
        {
            m_buffer_sending.pop_front();
            m_buffer_sending_offset.pop_front();
        }
        else
            break;
    }
}
void TcpSocket::SendData(QByteArray dtarray)
{
    m_mutex_write.lock();
    if (dtarray.size())
    {
        if (m_buffer_sending.empty()==true)
        {
            qint64 bytesWritten = write(dtarray.constData(),qMin(dtarray.size(),blockSize));
            if (bytesWritten < dtarray.size())
            {
                m_buffer_sending.push_back(dtarray);
                m_buffer_sending_offset.push_back(bytesWritten);
            }
        }
        else
        {
            m_buffer_sending.push_back(dtarray);
            m_buffer_sending_offset.push_back(0);
        }
    }
    m_mutex_write.unlock();
}
