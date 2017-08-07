#ifndef CENTERSTRUCTEXECTOR_H
#define CENTERSTRUCTEXECTOR_H

#include "timer.h"
#include "transmsg.h"
#include "structiserver_global.h"
#include "dao/csstructdao.h"

/**
 * @brief The CenterStructExector class 结构化任务下发
 * 定时扫描结构化任务表
 */
class STRUCTISERVERSHARED_EXPORT CenterStructExector :public AbstractExector
{
public:
    CenterStructExector();
protected:
    /**
     * @brief doExecute 定时扫描结构化任务表，当有任务执行时间到的时候,下发结构化任务
     * @param m_socks
     * @param context
     */
    void doExecute(QMap<QTcpSocket *, quint64> &m_socks, PushContext* context = 0);
    virtual void doSetArgs(QMap<QTcpSocket*,quint64> &socks);

protected slots:
    virtual void doExecute();

private:
    QMap<QTcpSocket*,quint64> m_socks;
    static QMutex mutex;
protected slots:
    /**
     * @brief on_RemoteHostClosed   远程客户端断开
     * @param clientUUID
     */
    virtual void on_RemoteHostClosed(const quint64 &clientUUID);
};

#endif // CENTERSTRUCTEXECTOR_H
