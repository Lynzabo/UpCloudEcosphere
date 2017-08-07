#ifndef RESPONSECONTEXT_H
#define RESPONSECONTEXT_H
#include <QtCore>
#include <QTcpSocket>
#include <transmsg.h>
#include "actionlib_global.h"

class ACTIONLIBSHARED_EXPORT ResponseContext : public QObject
{
    Q_OBJECT
public:
    explicit ResponseContext(QTcpSocket *client,const QString &clientKey);
    ~ResponseContext();
    /**
     * @brief getDatagram   获得装帧流
     * @return
     */
    QByteArray getDatagram() const;
    /**
     * @brief setDatagram   设置装帧流
     * @param value
     */
    void setDatagram(const QByteArray &value);

    bool getCanSend() const;
    /**
     * @brief setCanSend    是否发送出去,默认为发送出去
     * @param value
     */
    void setCanSend(bool value);

    bool getCanRedirect() const;
    /**
     * @brief setCanRedirect    是否重定向,默认为false
     * @param value
     * 当设置canRedirect重定向,并设置canSend不发送,则会由调度器处理转发到系统其它业务;
     * 当设置canRedirect重定向,并设置canSend发送,则会阻塞先处理重定向,在处理发送
     */
    void setCanRedirect(bool value);


    quint8 getMsgType() const;
    /**
     * @brief setMsgType    设置报文类型,注意,当需要重定向的时候会使用到报文类型区分不同报文
     * @param value
     */
    void setMsgType(const quint8 &value);

    MessageInfo *getMsgInfo() const;
    /**
     * @brief setMsgInfo    设置报文实体,注意,当重定向的时候使用它有效,其它地方暂时不需要
     * @param value
     */
    void setMsgInfo(MessageInfo *value);

private:
    //报文流
    QByteArray datagram;
    //当前客户端对象
    const QTcpSocket *client;
    //当前客户端UUID
    const QString &clientKey;
    //是否发送出去,默认为发送出去
    bool canSend;
    //是否重定向,当设置canRedirect重定向,并设置canSend不发送,则会由调度器处理转发到系统其它业务,默认为false
    bool canRedirect;
    //报文类型
    quint8 msgType;
    //报文体
    MessageInfo *msgInfo;
};

#endif // RESPONSECONTEXT_H
