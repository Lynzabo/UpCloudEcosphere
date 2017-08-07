#ifndef NODERSCHEDULEDOWNEXECTOR_H
#define NODERSCHEDULEDOWNEXECTOR_H

#include "base.h"
#include "db.h"
#include "action.h"
#include "timer.h"
#include "net.h"
#include "baseiclient.h"
#include "scheduleiclient_global.h"
#include "dao/nsscheduledao.h"

class SCHEDULEICLIENTSHARED_EXPORT NoderScheduleDownExector : public AbstractExector
{
    Q_OBJECT
public:
    NoderScheduleDownExector();
    ~NoderScheduleDownExector();
protected:
    /**
     * @brief doExecute 定时扫描控制传输任务表，当有任务执行时间到的时候,下发控制传输任务
     * @param m_socks
     * @param context
     */
    void doExecute(QMap<QTcpSocket*,quint64> &m_socks,PushContext *context = 0);
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

public slots:

    /**
     * @brief on_TransEnd    使用HTTP/FTP下载器一组文件下载完成
     * @param taskID
     */
    void on_TransEnd(const QString &taskID);

    /**
     * @brief on_TransSubFileEnd  使用HTTP/FTP下载器文件下载完成
     * @param fileUrl
     * @param destAbst
     */
    void on_TransSubFileEnd(const QString &taskID, const QString &fileUrl, const QString &destAbst);

    /**
     * @brief on_TransError  使用HTTP/FTP下载器下载出错
     * @param src
     * @param errMsg
     */
    void on_TransError(const QString &taskID, const QString &src, const QString &errMsg);
private:
    //服务端对象
    QMap<QTcpSocket *, quint64> m_centerSocks;
    //主动推送上下文
    PushContext *m_pushContext;
    //存放任务集下载出错文件,外层QMap的key存放任务UUID,里层QMap的key存放文件下载地址,value存放出错原因
    //注意:只有在下载出错的时候往里存放值,下载文件成功不放,当下载任务完成后,取出错信息,根据下载策略修改任务状态及反馈何种报文
    QMap<QString,QMap<QString,QString>*> m_mapTaskUUIDErrorFiles;
    //记录http单个文件下载完成入库锁
    QMutex *sfeMutex;
    //记录http/ftp任务处理完成入库锁
    QMutex *endMutex;
    //记录http单个文件下载出错入库锁
    QMutex *errMutex;
};

#endif // NODERSCHEDULEDOWNEXECTOR_H
