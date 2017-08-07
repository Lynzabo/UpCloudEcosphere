#ifndef ListDICTRunnable_H
#define ListDICTRunnable_H
#include <QtCore>
#include "duplex.h"
#include "base.h"
#include "erm.h"
#include "avro.h"
#include "baseiremote.h"
#include "basaloperairemoteui_global.h"
#include <QList>
class BASALOPERAIREMOTEUISHARED_EXPORT ListDictRunnable : public QRunnable
{
public:
    ListDictRunnable(QObject* object = 0);
    /**
     * @brief setSelectCondition    设置查询条件
     * @param conditionMap
     */
    void setSelectCondition(const QVariantMap &conditionMap);

    void setFilterPage(Page *page);

    void setFilterUnused();

    void setRecursion(bool recFlg = true);
protected:
    void run();
private:
    QObject* m_object;
    qint32 m_cbMsgId;
    QString m_cbMsg;
    QVariantMap conditionMap;
    Page* page;
    //不使用分页标志
    bool filterFlg;
    //只查当下一级标志,递归标志
    bool recursionFlg;
};

#endif // ListDICTRunnable_H
