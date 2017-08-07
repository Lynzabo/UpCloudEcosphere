#ifndef DRESPONSECONTEXT_H
#define DRESPONSECONTEXT_H
#include <QtCore>
#include <QTcpSocket>
#include <transmsg.h>
#include "duplexlib_global.h"


class DUPLEXLIBSHARED_EXPORT DResponseContext : public QObject
{
    Q_OBJECT
public:
    explicit DResponseContext(const QString &clientKey,const quint16 &ExecType,const QString &Params);
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
     * @brief getResponseState  获取状态码
     * @return
     */
    quint8 getResponseState() const;
    /**
     * @brief setResponseState  设置状态码
     * @param value
     */
    void setResponseState(const quint8 &value);
    /**
     * @brief getResponseContent    获取返回内容
     * @return
     */
    QString getResponseContent() const;
    /**
     * @brief setResponseContent    设置返回内容
     * @param value
     */
    void setResponseContent(const QString &value);

private:
    //状态码
    quint8 responseState;
    //返回内容
    QString responseContent;
    //操作类型码
    const quint16 &execType;
    //参数字符串
    const QString &params;
    //当前客户端对象
    const QTcpSocket *client;
    //当前客户端UUID
    const QString &clientKey;
};

#endif // DRESPONSECONTEXT_H
