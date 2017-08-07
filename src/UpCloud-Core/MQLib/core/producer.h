#ifndef PRODUCER_H
#define PRODUCER_H
#include <QtCore>
#include "mqlib_global.h"
/**
 * @brief The Producer class    消息生产者
 */
class MQLIBSHARED_EXPORT Producer : public QObject
{
    Q_OBJECT
public:
    explicit Producer(QObject *parent = 0);
    void setMsg();
signals:

public slots:
};

#endif // PRODUCER_H
