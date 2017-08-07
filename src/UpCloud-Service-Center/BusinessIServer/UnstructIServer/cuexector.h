#ifndef CENTERUNSTRUCTEXECTOR_H
#define CENTERUNSTRUCTEXECTOR_H
#include "base.h"
#include "db.h"
#include "timer.h"
#include "transmsg.h"
#include "unstructiserver_global.h"
#include "bean/csrutask.h"
#include "bean/csrusendaddr.h"
#include "bean/csrusendfiles.h"
#include "dao/csunstructdao.h"

/**
 * @brief The CenterUnstructExector class 非结构化任务下发
 * 定时扫描非结构化任务表
 */
class UNSTRUCTISERVERSHARED_EXPORT CenterUnstructExector : public AbstractExector
{
public:
    CenterUnstructExector();
protected:
    /**
     * @brief doExecute 定时扫描非结构化任务表，当有任务执行时间到的时候,下发非结构化任务
     * @param m_socks
     * @param context
     */
    void doExecute(QMap<QTcpSocket*,quint64> &socks, PushContext *context = 0);
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
private:
    QList< QList<CsRUnstructSendFiles>* > m_sendFileList;
    QList<ReqUnstructFilesDownloadInfo *> m_infoList;
};

#endif // CENTERUNSTRUCTEXECTOR_H
