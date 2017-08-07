#ifndef CONSUMER_H
#define CONSUMER_H
#include <QtCore>
#include "mqlib_global.h"

/**
 * @brief The Consumer class    消息消费者
 */
class MQLIBSHARED_EXPORT Consumer : public QObject
{
    Q_OBJECT
public:
    explicit Consumer(QObject *parent = 0);

signals:

public slots:
};

#endif // CONSUMER_H
