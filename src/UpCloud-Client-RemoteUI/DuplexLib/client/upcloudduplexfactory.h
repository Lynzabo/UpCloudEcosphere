#ifndef UPCLOUDDUPLEXFACTORY_H
#define UPCLOUDDUPLEXFACTORY_H

#include <QtCore>
#include "duplexlib_global.h"

#include "base.h"
#include "action.h"
#include "core/dpsender.h"
#include "core/dpresult.h"
#include "async/duplexasyncworker.h"

/**
 * @brief The UpCloudDuplexFactory class    上云全双工管理工厂
 */
class DUPLEXLIBSHARED_EXPORT UpCloudDuplexFactory : public QObject
{
    Q_OBJECT
    SINGLETON(UpCloudDuplexFactory)
signals:
    //往调度器写入数据
    void evt_send(QObject * socks, const QByteArray &datas);
    //从调度器通知同步客户端信息
    void evt_notice_sync_socks();
    //接收重定向数据
    void evt_receive_duplex(RequestContext * request,ResponseContext *response);
    //从调度器同步服务端信息
    void evt_sync_socks(QMap<QTcpSocket*,quint64> &m_server);
public slots:

    /**
     * @brief on_receive_duplex 接收重定向数据
     * @param request
     * @param response
     */
    void on_receive_duplex(RequestContext * request,ResponseContext *response);
public:
    /**
     * @brief createDPSender   生成请求者
     * @param priority
     * @return
     */
    DPSender *createDPSender();
private:
    DuplexAsyncWorker *asyncWorker;
};

#endif // UPCLOUDDUPLEXFACTORY_H
