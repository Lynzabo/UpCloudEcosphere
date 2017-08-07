#ifndef DREQUESTCONTEXT_H
#define DREQUESTCONTEXT_H
#include <QtCore>
#include <QTcpSocket>
#include <transmsg.h>
#include "duplexlib_global.h"

class DUPLEXLIBSHARED_EXPORT DRequestContext : public QObject
{
    Q_OBJECT
public:
    explicit DRequestContext(const QString &clientKey,DataGramInfo *gram,const quint16 &ExecType,const QString &Params);
    /**
     * @brief getExecType   获取操作类型码
     * @return
     */
    const quint16 &getExecType() const;
    /**
     * @brief getParams 获取参数字符串
     * @return
     */
    const QString &getParams() const;
    /**
     * @brief getClientKey  获取当前客户端UUID
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
     * @brief getUUID   获取固定码
     * @return
     */
    const quint64 &getUUID() const;
    /**
     * @brief getRequestID  获取请求码
     * @return
     */
    const QString &getRequestID() const;
    /**
     * @brief getTimestamp  获取时间戳
     * @return
     */
    const quint64 &getTimestamp() const;
    /**
     * @brief getDataLength 报文体长度
     * @return
     */
    const quint32 &getDataLength() const;
    /**
     * @brief getMessage    获取报文体
     * @return
     */
    const QString &getMessage() const;

private:
    //操作类型码
    const quint16 &execType;
    //参数字符串
    const QString &params;
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

#endif // DREQUESTCONTEXT_H
