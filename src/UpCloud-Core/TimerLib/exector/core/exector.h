#ifndef EXECTOR_H
#define EXECTOR_H
#include <QtCore>
#include <QTcpSocket>
#include "context/pushcontext.h"
#include "timerlib_global.h"
/**
 * @brief The Request class 定时任务组执行器,如果是多个任务,执行emit
 */
class TIMERLIBSHARED_EXPORT Exector : public QObject
{
    Q_OBJECT
public:
    explicit Exector(QObject *parent = 0);
    /**
     * @brief doInit    当到达定时时间,比如在这里可以打开数据库连接
     * 到达顺序1
     */

    ~Exector();
    virtual void doInit() = 0;

    /**
     * @brief doExecute 定时执行任务方法,比如定时下发多个任务;客户端定时解析数据文件,待解析数据完后发出报文
     * @param m_socks   可推送的客户端列表
     * 到达顺序2
     */
    virtual void doExecute(QMap<QTcpSocket*,quint64> &m_socks,PushContext *context = 0) = 0;
    /**
     * @brief doDestory 销毁,在进析构前会先进这个接口,比如在这里可以关闭数据库连接
     * 到达顺序3
     */
    virtual void doDestory() = 0;

    virtual void doSetArgs(QMap<QTcpSocket*,quint64> &socks) = 0;
public slots:
    /**
     * @brief on_RemoteHostClosed   远程客户端断开
     * @param clientUUID
     */
    virtual void on_RemoteHostClosed(const quint64 &clientUUID) = 0;
    virtual void doExecute() = 0;
signals:
    //写入数据
    void evt_write(PushContext *context);
};

#endif // EXECTOR_H
