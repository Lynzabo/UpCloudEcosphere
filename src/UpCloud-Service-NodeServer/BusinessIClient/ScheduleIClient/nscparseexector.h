#ifndef NODERSCHEDULEPARSEEXECTOR_H
#define NODERSCHEDULEPARSEEXECTOR_H

#include "base.h"
#include "db.h"
#include "action.h"
#include "timer.h"
#include "net.h"
#include "baseiclient.h"
#include "scheduleiclient_global.h"
#include "dao/nsscheduledao.h"
#include "util/taskexecpoolimpl.h"
#include "avro.h"

class SCHEDULEICLIENTSHARED_EXPORT NoderScheduleParseExector : public AbstractExector
{
    Q_OBJECT
public:
    NoderScheduleParseExector();
    ~NoderScheduleParseExector();
protected:
    /**
     * @brief doExecute 定时扫描控制传输可执行任务表，当有任务执行时间到的时候,执行控制传输任务
     * @param m_socks
     * @param context
     */
    void doExecute(QMap<QTcpSocket*,quint64> &socks, PushContext *context = 0);
    virtual void doSetArgs(QMap<QTcpSocket*,quint64> &socks);

protected slots:
    virtual void doExecute();

private:
    QMap<QTcpSocket*,quint64> m_socks;

signals:
    void endLoop();

protected slots:
    /**
     * @brief on_RemoteHostClosed   远程客户端断开
     * @param clientUUID
     */
    virtual void on_RemoteHostClosed(const QString &clientUUID);

private slots:
    void on_execBegin(const QString &taskName);
    void on_execEnd(const QString& taskName, const QString &result);

private:
    //In
    //服务端对象
    QMap<QTcpSocket*, quint64> m_centerSocks;
    //主动推送上下文
    PushContext* m_pushContext;

    //Out
    //反馈报文对象列表
    QList<ReqScheduleTaskExecStatus*> m_reqEntitys;    
    //本次扫描的任务执行结果映射表<taskUUID, 任务执行结果>，一个任务对应一个任务执行结果
    QMap<QString, ResultInfo*> m_results;


    //Assistant
    //本次扫描的所有可用任务列表
    QList<NsRScheduleTask> m_usableScheduleExecTasks;
    //本次扫描任务映射表<taskUUID, 任务执行池>，一个任务对应一个任务执行池
    QMap<QString,  TaskExecPool*> m_pools;

    //检查是否所有任务都完成
    void checkFinished();
    //清理资源
    void clear();
};

#endif // NODERSCHEDULEPARSEEXECTOR_H
