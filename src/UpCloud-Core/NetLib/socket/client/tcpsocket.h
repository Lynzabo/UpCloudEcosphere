#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#include <QTcpSocket>
#include "netlib_global.h"
#include "base.h"
class QMutex;

class NETLIBSHARED_EXPORT TcpSocket : public QTcpSocket
{
    Q_OBJECT

public:
    TcpSocket(QObject *parent,int nPayLoad = 4096);
    ~TcpSocket();
    QString uuid() const;
    void setUuid(const QString &uuid);

private:
    QString m_uuid;
    int blockSize;
    //自定义数据块的大小
    QList<QByteArray> m_buffer_sending;
    //存放每个块的位置
    QList<qint64> m_buffer_sending_offset;
    QMutex m_mutex_write;
public slots:
    /**
     * @brief on_some_data_sended   发送服务端块数据
     * 发送数据时候,进行切块,根据块发送
     */
    void some_data_sended(qint64);
    /**
     * @brief SendData  往服务器发送数据,在执行该函数结束后会自动进some_data_sended进行自定义块大小发送
     * @param dtarray
     */
    void SendData(QByteArray dtarray);
};

#endif // TCPSOCKET_H
