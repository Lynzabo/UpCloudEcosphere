#ifndef CSBRIDGEDAO_H
#define CSBRIDGEDAO_H

#include "base.h"
#include "db.h"
#include "transmsg.h"

#include "../bean/csterminal.h"

class CSBridgeDao
{
public:
    CSBridgeDao();
    /**
     * @brief terminateIsExist 查询此终端是否已经在数据库中
     * @param terminateUUID    终端固定码
     * @return                 存在返回true不存在返回false
     */
    static bool terminateIsExist(quint64 terminateUUID);

    /**
     * @brief updateTerminate   更新终端在数据库中的状态
     * @param terminateUUID     固定码
     * @param IP                IP地址
     * @param MAC               MAC地址
     * @param pubKey            公钥
     * @param priKey            私钥
     * @param state             状态
     * @param onlineTime        上线时间
     * @param offlineTime       离线时间
     */
    static void updateTerminate(quint64& terminateUUID,
                                QString& IP,
                                QString& MACAddr,
                                QString& pubKey,
                                QString& priKey,
                                quint8 state,
                                QString& onlineTime,
                                QString& offlineTime);

    /**
     * @brief addTerminate  向数据库中添加终端设备
     * @param terminate     终端设备实体
     */
    static void addTerminate(CsTerminal& terminate);
};

#endif // CSBRIDGEDAO_H
