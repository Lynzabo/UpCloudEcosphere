#ifndef TERMINALKEYUTIL_H
#define TERMINALKEYUTIL_H
#include "base.h"
#include "../bean/csterminal.h"
#include "../baseiserverlib_global.h"
/**
 * @brief The TerminalUUIDUtil class    终端密钥维护工具类
 */
class  BASEISERVERLIBSHARED_EXPORT TerminalKeYUtil
{
public:
    static TerminalKeYUtil& getInstance()
    {
        return *m_instance;
    }

    static void release()
    {
        delete m_instance;
        m_instance = 0;
    }

private:
    TerminalKeYUtil();
    ~TerminalKeYUtil();
    static TerminalKeYUtil* m_instance;
public:
    void init();
    /**
     * @brief updateTerminalKey 更换密钥
     * @param uuid  固定码
     * @param newPubKey    新的公钥
     * @param newPriKey    新的私钥
     * @return
     */
    bool updateTerminalKey(const quint64 &uuid, const QString& newPubKey, const QString& newPriKey);

    /**
     * @brief getTerminalPubKey 获取公钥
     * @param uuid      固定码
     * @param pubKey    公钥
     */
    bool getTerminalPubKey(const quint64 &uuid, QString& pubKey) const;

    /**
     * @brief getTerminalPribKey 获取私钥
     * @param uuid      固定码
     * @param priKey    私钥
     */
    bool getTerminalPriKey(const quint64 &uuid, QString& priKey) const;

    /**
     * @brief terminalToJson  节点服务器信息实体转换为JSON串
     * @param msg
     * @param terminal
     */
    static void terminalToJson(QString &msg,const CsTerminal terminal);
    /**
     * @brief terminalToJson 节点服务器信息链表实体转换为JSON串
     * @param msg
     * @param terminal
     */
    static void terminalToJson(QString &msg, const QList<CsTerminal> terminalList);
    /**
     * @brief terminalFromJson JSON串转换为节点服务器信息
     * @param terminal
     * @param msg
     */
    static bool terminalFromJson(CsTerminal &terminal, const QString &msg);
    /**
     * @brief terminalFromJson  JSON串转换为节点服务器信息链表
     * @param terminalList
     * @param msg
     * @return
     */
    static bool terminalFromJson(QList<CsTerminal> &terminalList,const QString &msg);
private:
    QMap<quint64, CsTerminal> m_terminalKeyMap;
    QMutex mutex;
};

#endif // TERMINALKEYUTIL_H
