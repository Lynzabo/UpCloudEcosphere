#ifndef TIMERCONTROLLER_H
#define TIMERCONTROLLER_H
#include <QtCore>
#include "timerlib_global.h"
#include <QTcpSocket>
#include "timer.h"
/**
 * @brief The Request class 定时群组控制器
 * 注:执行器
 */
class TIMERLIBSHARED_EXPORT TimerController : public QObject
{
    Q_OBJECT
public:
    explicit TimerController(QObject *parent = 0);

signals:
    //往调度器写入数据
    void evt_write(QObject* socks, const QByteArray &datas);
    //从调度器通知同步客户端信息
    void evt_notice_sync_socks(quint8 clientType);
    //远程服务端断开
    void evt_RemoteHostClosed(const quint64 &clientUUID);
public slots:
    /**
     * @brief start 开启计时器群组
     */
    virtual void on_start() = 0;
    /**
     * @brief start 停止计时器群组
     */
    virtual void on_stop() = 0;
    /**
     * @brief on_write  读取Exector数据
     * @param context
     */
    virtual void on_write(PushContext *context) = 0;


    /**
     * @brief on_sync_socks   同步客户端数据
     * @param m_clients
     */
    void on_sync_socks(QMap<QTcpSocket*,quint64> &m_clients);

    /**
     * @brief on_SocketError    远程客户端断开
     * @param senderSock
     */
     void on_RemoteHostClosed(QTcpSocket *senderSock);
public:
    //Socket  固定码（quint64 机器唯一标示）
    QMap<QTcpSocket*,quint64> m_socks;
    //执行者
    Exector *ector;
};

#endif // TIMERCONTROLLER_H
