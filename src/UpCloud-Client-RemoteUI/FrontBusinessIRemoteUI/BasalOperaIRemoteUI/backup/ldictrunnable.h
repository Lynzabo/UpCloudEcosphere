#ifndef ListDICTRunnable_H
#define ListDICTRunnable_H
#include <QtCore>
#include "duplex.h"
#include "base.h"
#include "avro.h"
#include "baseiremote.h"
#include "basaloperairemoteui_global.h"
#include <QList>
class BASALOPERAIREMOTEUISHARED_EXPORT ListDictRunnable : public QRunnable
{
public:
    ListDictRunnable(QObject* object = 0);
    void run();
    /**
     * @brief setSelectCondition    设置查询条件
     * @param conditionMap
     */
    void setSelectCondition(const QVariantMap &conditionMap);
private:
    QObject* m_object;
    qint32 m_cbMsgId;
    QString m_cbMsg;
    QVariantMap conditionMap;
};

#endif // ListDICTRunnable_H
