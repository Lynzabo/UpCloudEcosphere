#ifndef HEARTTHROBCLIENTEXECTOR_H
#define HEARTTHROBCLIENTEXECTOR_H
#include <QtCore>
#include "timer.h"
#include "transmsg.h"
#include "hthrobsiclient_global.h"

class HTHROBSICLIENTSHARED_EXPORT HeartthrobClientExector : public AbstractExector
{
public:
    HeartthrobClientExector();
protected:
    /**
     * @brief doExecute 拼装心跳包文并发送出去
     * @param m_socks   服务端对象
     * 到达顺序2
     */
    virtual void doExecute(QMap<QTcpSocket*,quint64> &m_socks,PushContext *context = 0);
    virtual void doSetArgs(QMap<QTcpSocket*,quint64> &socks);

protected slots:
    virtual void doExecute();

private:
    QMap<QTcpSocket*,quint64> m_socks;
};

#endif // HEARTTHROBCLIENTEXECTOR_H
