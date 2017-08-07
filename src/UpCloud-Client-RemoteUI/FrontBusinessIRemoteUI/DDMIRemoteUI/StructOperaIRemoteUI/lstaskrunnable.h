#ifndef LISTSTRUCTTASKRUNNABLE_H
#define LISTSTRUCTTASKRUNNABLE_H
#include <QtCore>
#include "base.h"
#include "erm.h"
#include "avro.h"
#include "duplex.h"
#include "structoperairemoteui_global.h"
#include "baseiremote.h"
class STRUCTOPERAIREMOTEUISHARED_EXPORT ListStructTaskRunnable : public QRunnable
{
public:
    ListStructTaskRunnable(QObject* object = 0);
protected:
    void run();
public:
    void setTaskInfo(const QVariantMap & map);
    /**
     * @brief setFilterPage 设置过滤Page
     * @param _page
     */
    void setFilterPage(Page *_page);
private:
    QObject* m_object;
    qint32 m_cbMsgId;
    QString m_cbMsg;
    QVariantMap m_map;
    //在UI会对该指针进行释放
    Page* m_page;
};

#endif // LISTSTRUCTTASKRUNNABLE_H
