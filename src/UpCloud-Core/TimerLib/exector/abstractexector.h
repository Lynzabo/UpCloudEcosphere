#ifndef ABSTRACTEXECTOR_H
#define ABSTRACTEXECTOR_H
#include <QtCore>
#include "timerlib_global.h"
#include "core/exector.h"
class TIMERLIBSHARED_EXPORT AbstractExector : public Exector
{
public:
    AbstractExector();
protected:
    /**
     * @brief doInit    当到达定时时间,比如在这里可以打开数据库连接
     * 到达顺序1
     */
    virtual void doInit();

    /**
     * @brief doExecute 定时执行任务方法,比如定时下发多个任务;客户端定时解析数据文件,待解析数据完后发出报文
     * @param m_socks   可推送的客户端列表
     * 到达顺序2
     */
    virtual void doExecute(QMap<QTcpSocket*,quint64> &m_socks,PushContext *context = 0);
    /**
     * @brief doDestory 销毁,在进析构前会先进这个接口,比如在这里可以关闭数据库连接
     * 到达顺序3
     */
    virtual void doDestory();

    virtual void doSetArgs(QMap<QTcpSocket*,quint64> &socks);
protected slots:
    /**
     * @brief on_RemoteHostClosed   远程客户端断开
     * @param clientUUID
     */
    virtual void on_RemoteHostClosed(const quint64 &clientUUID);
    virtual void doExecute();
};

#endif // ABSTRACTEXECTOR_H
