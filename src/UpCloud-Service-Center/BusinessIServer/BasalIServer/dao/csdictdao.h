#ifndef CSDICTDAO_H
#define CSDICTDAO_H
#include <QtCore>
#include "../bean/csdict.h"
#include "db.h"
class CSDictDao
{
public:
    CSDictDao();
    /**
     * @brief addCsDict  向表CS_DICT添加一条记录
     * @param task
     */
    static void addCsDict(const CsDict &task);
    /**
     * @brief dirCsDict 使用code和supUuid作为条件查看记录
     * @param code
     * @param supUuid
     * @return
     */
    static QList<CsDict> dirCsDict(const QString &code, const QString supUuid);
    /**
     * @brief dirCsDict 查询表CS_DICT所有的记录
     * @return
     */
    static QList<CsDict> dirCsDict(void);
    /**
     * @brief dirCsDict 查询表CS_DICT所有的记录
     * @param paramsMap 查询条件对象
     * @return
     */
    static QList<CsDict> dirCsDict(const QVariantMap &paramsMap);
    /**
     * @brief pageDict 查询表CS_DICT所有的记录
     * @param selectDict    查询条件对象
     * @return
     */
    static QList<CsDict> pageDict(const QVariantMap &paramsMap, Page *page);
    /**
     * @brief delCsdict 删除指定的CS_DICT表的记录
     * @param codes 被删除的字典的编码,删除当前记录和所有子记录
     * @return
     */
    static void delCsDict(const QStringList &uuids);
    /**
     * @brief updateCsDict 修改指定的CS_DICT表的记录
     * @param task
     */
    static void updateCsDict(const QList<CsDict> &taskList);
    /**
     * @brief itemCsDict    使用任务UUID获取任务信息
     * @param uuid  任务UUID
     * @return
     */
    static CsDict itemCsDict(const QString &uuid);
private:
    /**
     * @brief mapToCsDict
     * @param rowMap
     * @return
     */
    static CsDict mapToCsDict(const QVariantMap& rowMap);
};

#endif // CSDICTDAO_H
