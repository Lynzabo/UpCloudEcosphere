#ifndef RESPONSE_H
#define RESPONSE_H
#include <QtCore>
#include "actionlib_global.h"
/**
 * @brief The Request class 处理网络响应纯虚基类
 * 注:按上云报文装帧标准,发送方发送请求前享有如下接口
 */

class ACTIONLIBSHARED_EXPORT Response : public QObject
{
    Q_OBJECT
public:
    explicit Response(QObject *parent = 0);

signals:

public slots:
};

#endif // RESPONSE_H
