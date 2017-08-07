#ifndef NODERSTRUCTPARSEEXECTOR_H
#define NODERSTRUCTPARSEEXECTOR_H


#include "base.h"
#include "db.h"
#include "action.h"
#include "timer.h"
#include "net.h"
#include "baseiclient.h"
#include "structiclient_global.h"
#include "dao/nsstructdao.h"
#include "util/parsesdpoolimpl.h"

class STRUCTICLIENTSHARED_EXPORT NoderStructParseExector : public AbstractExector
{
    Q_OBJECT
public:
    NoderStructParseExector();
    ~NoderStructParseExector();
protected:
    /**
     * @brief doExecute 定时扫描结构化可解析任务表，当有任务执行时间到的时候,执行解析任务
     * @param m_socks
     * @param context
     */
    void doExecute(QMap<QTcpSocket*,quint64> &socks,PushContext *context = 0);
    virtual void doSetArgs(QMap<QTcpSocket*,quint64> &socks);

protected slots:
    virtual void doExecute();

private:
    QMap<QTcpSocket*,quint64> m_socks;
    static QMutex mutex;
signals:
    void endLoop();

private:
    //In
    //服务端对象
    QMap<QTcpSocket*, quint64> m_centerSocks;
    //主动推送上下文
    PushContext* m_pushContext;

    //Out
    //反馈报文对象列表
    QList<ReqStructTaskExecStatus*> m_reqEntitys;
    //本次扫描的错误映射表<taskUUID, 错误信息>，一个任务对应一个错误信息
    QMap<QString, ResultInfo*> m_errors;

    //Assistant
    //本次扫描的所有可用任务列表
    QList<NsRStructTask> m_usableStructParseTasks;
    //本次扫描任务映射表<taskUUID, 解析线程池>，一个任务对应一个解析线程池
    QMap<QString,  ParseSDPool*> m_pools;

    //检查是否所有任务都完成
    void checkFinished();
    //清理资源
    void clear();
private slots:
    /**
     * @brief on_parseBegin 一个任务解析开始
     */
    void on_parseBegin();
    /**
     * @brief on_parseEnd   一个任务解析完成
     */
    void on_parseEnd();
    /**
     * @brief on_parseOneFileEnd    一个文件解析完成
     * @param fileName  文件名
     */
    void on_parseOneFileEnd(const QString& fileName);    
    /**
     * @brief on_parseError 一个文件解析出错
     * @param fileName  文件名
     * @param errMsg    出错信息
     */
    void on_parseError(const QString& fileName, const QString &errMsg);
    /**
     * @brief on_parseProcess   一个任务解析进度
     * @param parsedCount   已解析完成的文件数目
     */
    void on_parseProcess(quint32 parsedCount);

};

#endif // NODERSTRUCTPARSEEXECTOR_H
