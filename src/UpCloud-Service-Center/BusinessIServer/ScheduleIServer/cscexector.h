#ifndef CENTERSCHEDULEEXECTOR_H
#define CENTERSCHEDULEEXECTOR_H

#include "base.h"
#include "db.h"
#include "timer.h"
#include "transmsg.h"
#include "scheduleiserver_global.h"
#include "dao/csscheduledao.h"

/**
 * @brief The CenterScheduleExector class 控制传输任务下发
 * 定时扫描控制传输任务表
 */

class SCHEDULEISERVERSHARED_EXPORT CenterScheduleExector :public AbstractExector
{
public:
    CenterScheduleExector();
protected:
    /**
     * @brief doExecute 定时扫描控制传输任务表，当有任务执行时间到的时候,下发控制传输任务
     * @param m_socks
     * @param context
     */
    void doExecute(QMap<QTcpSocket*, quint64> &m_socks, PushContext* context = 0);
    virtual void doSetArgs(QMap<QTcpSocket*,quint64> &socks);

protected slots:
    virtual void doExecute();

private:
    QMap<QTcpSocket*,quint64> m_socks;

protected slots:
    /**
     * @brief on_RemoteHostClosed   远程客户端断开
     * @param clientUUID
     */
    virtual void on_RemoteHostClosed(const quint64 &clientUUID);
};

#endif // CENTERSCHEDULEEXECTOR_H
