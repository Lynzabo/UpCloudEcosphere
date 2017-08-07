#ifndef PUSHCONTEXT_H
#define PUSHCONTEXT_H
#include <QtCore>
#include <QTcpSocket>
#include "transmsg.h"
#include "timerlib_global.h"
/**
 * @brief The PushContext class 主动推送上下文
 */
class TIMERLIBSHARED_EXPORT PushContext : public QObject
{
    Q_OBJECT
public:
    explicit PushContext(QObject *parent = 0);
    ~PushContext();
    /**
     * @brief getSocks  获取要推送报文的所有客户端
     * @return
     */
    QVector<quint64> getSocks() const;
    /**
     * @brief setSocks  指定要推送给哪些客户端报文
     * @param value
     */
    void setSocks(const QVector<quint64> &value);
    /**
     * @brief getMessage    获取报文封包实体对象
     * @return
     */
    MessageInfo *getMessage() const;
    /**
     * @brief setMessage    设置报文封装封装对象
     * @param value
     */
    void setMessage(MessageInfo *value);

signals:

public slots:
private:
    //要推送的客户端
    QVector<quint64> socks;
    //报文封包实体
    MessageInfo *message;
};

#endif // PUSHCONTEXT_H
