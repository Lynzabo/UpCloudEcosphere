#ifndef FILTER_H
#define FILTER_H
#include <QtCore>
#include "transmsg.h"
#include <QTcpSocket>
#include "actionlib_global.h"
#include "context/requestcontext.h"
#include "context/responsecontext.h"

class ACTIONLIBSHARED_EXPORT Filter : public QObject
{
    Q_OBJECT
public:
    explicit Filter(QObject *parent = 0);
    /**
     * @brief doFilter  过滤客户请求并作相应操作
     * @param client    客户端对象
     * @param clientKey 客户端主键
     * @param gram  装帧报文
     */
    virtual void doFilter(QTcpSocket *client = 0, const QString &clientKey = 0, DataGramInfo *gram = 0) = 0;
signals:
    //发送报文
    void evt_write(QTcpSocket * client,const QByteArray &data);
    //重定向到其它业务
    void evt_redirect(RequestContext * request,ResponseContext *response);
public slots:
    /**
     * @brief on_read   读取请求来数据
     * @param client
     * @param clientKey
     * @param gram
     */
    virtual void on_read(QTcpSocket * client, const QString &clientKey, DataGramInfo *gram) = 0;
};

#endif // FILTER_H
