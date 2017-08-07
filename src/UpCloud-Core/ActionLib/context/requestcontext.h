#ifndef REQUESTCONTEXT_H
#define REQUESTCONTEXT_H
#include <QtCore>
#include <QTcpSocket>
#include <transmsg.h>
#include "actionlib_global.h"
class ACTIONLIBSHARED_EXPORT RequestContext : public QObject
{
    Q_OBJECT
public:
    explicit RequestContext(QTcpSocket *client,const QString &clientKey,DataGramInfo *gram);

    ~RequestContext();
    /**
     * @brief getClient 获取当前客户端对象
     * @return
     */
    const QTcpSocket *getClient() const;
    /**
     * @brief getClientKey  获取当前客户端对象
     * @return
     */
    const QString &getClientKey() const;
    /**
     * @brief getGram   获取当前报文装帧格式
     * @return
     */
    const DataGramInfo *getGram() const;
    /**
     * @brief getMsgType    获取报文类型
     * @return
     */
    const quint8 &getMsgType() const;
    /**
     * @brief getUUID   固定码
     * @return
     */
    const quint64 &getUUID() const;
    /**
     * @brief getRequestID  请求码
     * @return
     */
    const QString &getRequestID() const;
    /**
     * @brief getTimestamp  时间戳
     * @return
     */
    const quint64 &getTimestamp() const;
    /**
     * @brief getDataLength 报文体长度
     * @return
     */
    const quint32 &getDataLength() const;
    /**
     * @brief getMessage    报文体
     * @return
     */
    const QString &getMessage() const;

private:
    //当前客户端对象
    const QTcpSocket *client;
    //当前客户端UUID
    const QString &clientKey;
    //当前报文装帧格式
    const DataGramInfo *gram;
    //报文类型
    const quint8 &msgType;
    //固定码
    const quint64 &UUID;
    //请求码
    const QString &requestID;
    //时间戳
    const quint64 &timestamp;
    //报文体长度
    const quint32 &dataLength;
    //报文体
    const QString &message;
};

#endif // REQUESTCONTEXT_H
