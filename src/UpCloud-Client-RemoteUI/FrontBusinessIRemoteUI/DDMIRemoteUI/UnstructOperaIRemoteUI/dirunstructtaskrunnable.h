#ifndef DIRUNSTRUCTTASKRUNNABLE_H
#define DIRUNSTRUCTTASKRUNNABLE_H
#include <QtCore>
#include "base.h"
#include "avro.h"
#include "duplex.h"
#include "page.h"
#include "unstructoperairemoteui_global.h"
#include "baseiremote.h"

class UNSTRUCTOPERAIREMOTEUISHARED_EXPORT DirUnstructTaskRunnable : public QRunnable
{
public:
    DirUnstructTaskRunnable(QObject* object = 0);
protected:
    void run();
public:
    /**
     * @brief setListCondition  设置查询条件
     * @param map
     * @param page
     */
    void setListCondition(const QVariantMap &map);
    /**
     * @brief setFilterPage 设置过滤Page
     * @param _page
     */
    void setFilterPage(Page *_page);
private:
    QObject *m_object;
    //消息ID
    qint32 cbMsgId;
    //消息内容
    QString cbMsg;
    //查询条件
    QVariantMap m_map;
    //在UI会对该指针进行释放
    Page* m_page;

};

#endif // DIRUNSTRUCTTASKRUNNABLE_H
