#ifndef CSGROUPANDCLINETDAO_H
#define CSGROUPANDCLINETDAO_H
#include <QtCore>
#include <base.h>
#include "../bean/cscgroup.h"
#include "../bean/cscgroupassoc.h"
#include "../bean/cscextendinfo.h"
#include "../bean/vcscgroupassoc.h"
#include "db.h"
#include <QList>


class CsGroupAndClinetDao
{
public:
    CsGroupAndClinetDao();
    /**
     * @brief delGroupClient 递归删除群组
     * @param uuid
     */
    static void delGroupClient(const QString & uuid);
    /**
     * @brief delGroupClientAssoc 删除群组组指定的节点服务器信息
     * @param taskList
     */
    static void delGroupClientAssoc(const QList<CsClientGroup> &taskList);
    /**
     * @brief delGroupClientAssoc 删除群组指定的节点服务信息
     * @param task
     * @param nodes
     */
    static void delGroupClientAssoc(const QVariantMap &params);
    /**
     * @brief dirGroupClient 添加群组
     * @param task
     */
    static void addGroupClient(const CsClientGroup &task);
    /**
     * @brief addGroupClient  添加群组
     * @param params
     */
    static void addGroupClient(const QVariantMap &params);
    /**
     * @brief addGroupClientAssoc 给指定的群组添加节点服务器
     * @param task
     * @param nodes
     */
    static void addGroupClientAssoc(const CsClientGroupAssoc &task,const QStringList & nodes  );
    /**
     * @brief dirGroupClient 返回指定的查询记录
     * @param uuid
     * @return
     */
    static CsClientGroup dirGroupClient(const QString & uuid);
    /**
     * @brief dirGroupClient 查询群组
     * @param task
     * @return
     */
    static QList<CsClientGroup> dirGroupClient(const CsClientGroup &task);
    /**
     * @brief dirClientExtendInfo 查询节点服务器扩展信息
     * @param clientUuid
     * @return
     */
    static QList<CsClientExtendInfo> dirClientExtendInfo(const QString &clientUuid);
    /**
     * @brief dirGroupClient 递归查询
     * @param codes 递归查询参数
     * @return
     */
    static QList<CsClientGroup> dirGroupClient(const QStringList& codes);
    /**
     * @brief dirGroupClientBySupUuid 查询节点服务器
     * @param supUuids
     * @return
     */
    static QList<CsClientGroup> dirGroupClientBySupUuid(const QStringList& supUuids,const quint32 page);
    static QList<VCsClientGroupAssoc> dirGroupClientAssoc(const QStringList &groupList, const quint32 page);
    /**
     * @brief dirGroupClientAssoc 查询多条记录
     * @param uuid
     * @param nodes
     * @return
     */
    static QList<CsClientGroupAssoc> dirGroupClientAssoc(const QString &groupUuid,const QStringList &nodes = {});
    /**
     * @brief itemGroupClient 查询一条记录
     * @param uuid
     * @return
     */
    static CsClientGroup itemGroupClient(const QString &uuid);
    /**
     * @brief updateGroupClient 修改群组
     * @param task
     * @return
     */
    static void updateGroupClient(const CsClientGroup &task);
    static void updateGroupAssoc(const QString &uuid,const quint8 state);
    //---------------------移动 顺序----------------------------begin
    /**
     * @brief moveNodeToGroupIn  节点移动到组内
     * @param params
     */
    static void moveNodeToGroupIn(const QVariantMap &params);
    /**
     * @brief moveNodeToGroupOut 节点移动到组外
     * @param params
     */
    static void moveNodeToGroupOut(const QVariantMap &params);
    /**
     * @brief moveGroupToGroupIn 组移动到组内
     * @param params
     */
    static void moveGroupToGroupIn(const QVariantMap &params);
    /**
     * @brief moveGroupToGroupOut 组移动到组外
     * @param params
     */
    static void moveGroupToGroupOut(const QVariantMap &params);
    //---------------------移动 顺序----------------------------end

private:
    static CsClientGroup mapToGroupClient(const QVariantMap & rowMap);
    static CsClientGroupAssoc mapToGroupClientAssoc(const QVariantMap &rowMap);
    static VCsClientGroupAssoc mapToVGroupClientAssoc(const QVariantMap &rowMap);
    static CsClientExtendInfo mapToClientExtendInfo(const QVariantMap &rowMap);
};

#endif // CSGROUPANDCLINETDAO_H
