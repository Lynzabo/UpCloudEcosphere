#ifndef CSTERMINALDAO_H
#define CSTERMINALDAO_H

#include "base.h"
#include "transmsg.h"
#include "../bean/csterminal.h"
#include "../baseiserverlib_global.h"

class BASEISERVERLIBSHARED_EXPORT CSTerminalDao
{
public:
    CSTerminalDao();
    /**
     * @brief listTerminalByClientUUid 模糊查询节点服务器信息
     * @param clientUUid
     * @return
     */
    static QList<CsTerminal> listTerminalByClientUUid(const QString &clientUUid);
    static QList<CsTerminal> listTerminalByState(const quint8 state);
    static QList<CsTerminal> listTerminalByStateAndType(const quint8 state, const qint8 type);
    static QList<CsTerminal> listTerminalByRunState(const quint8 state);
    static QList<quint64> listTerminalUUIDByType(const quint8 type);
    /**
     * @brief terminateIsExist 查询此终端是否已经在数据库中
     * @param terminateUUID    终端固定码
     * @return                 存在返回true不存在返回false
     */
    static bool terminateIsExist(const quint64& terminateUUID);

    /**
     * @brief updateTerminate   更新终端在数据库中的状态
     * @param terminateUUID     固定码
     * @param IP                IP地址
     * @param MAC               MAC地址
     * @param pubKey            公钥
     * @param priKey            私钥
     * @param runState          转态
     * @param onlineTime        上线时间
     * @param offlineTime       离线时间
     */
    static void updateTerminate(const quint64& terminateUUID,
                                const QString& IP,
                                const QString& MACAddr,
                                const QString& pubKey,
                                const QString& priKey,
                                const quint8 runState,
                                const QString& onlineTime,
                                const QString& offlineTime);

    static void updateTerminateKey(const quint64& terminateUUID,
                                   const QString& pubKey,
                                   const QString& priKey);

    /**
     * @brief addTerminate  向数据库中添加终端设备
     * @param terminate     终端设备实体
     */
    static void addTerminate(const CsTerminal& terminate);

private:
    static CsTerminal mapToCsTerminal(const QVariantMap &rowMap);
};

#endif // CSTERMINALDAO_H
