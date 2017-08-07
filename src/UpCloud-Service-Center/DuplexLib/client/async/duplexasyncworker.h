#ifndef DUPLEXASYNCWORKER_H
#define DUPLEXASYNCWORKER_H
#include <QtCore>
#include "base.h"
#include "action.h"
#include "client/core/dpsender.h"
#include "client/core/dpresult.h"


class DuplexAsyncWorker : public QThread
{
    Q_OBJECT
public:
    DuplexAsyncWorker();
    ~DuplexAsyncWorker();
protected:
    void  run();
private:
public slots:
    /**
     * @brief on_sync_socks   同步客户端数据
     * @param m_clients
     */
    void on_sync_socks(QMap<QTcpSocket*,QString> &m_clients)
    {
        this->m_socks.clear();
        this->m_socks = m_clients;
    }
    /**
     * @brief on_receive_duplex 接收重定向数据
     * @param request
     * @param response
     */
    void on_receive_duplex(RequestContext * request,ResponseContext *response);
private slots:
    void pullSender();
signals:
    //从调度器通知同步客户端信息
    void evt_notice_sync_socks();
    //往调度器写入数据
    void evt_send(QVector<QObject *> socks, const QByteArray &datas);
private:
    QMap<QTcpSocket*,QString> m_socks;
};

#endif // DUPLEXASYNCWORKER_H
