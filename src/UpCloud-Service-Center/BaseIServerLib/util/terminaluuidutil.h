#ifndef TERMINALUUIDUTIL_H
#define TERMINALUUIDUTIL_H
#include "base.h"
#include "transmsg.h"
#include "../baseiserverlib_global.h"
/**
 * @brief The TerminalUUIDUtil class    中心服务器固定码生成更新工具类
 */
class BASEISERVERLIBSHARED_EXPORT TerminalUUIDUtil
{
public:
    static TerminalUUIDUtil& getInstance()
    {
        return *m_instance;
    }

    static void release()
    {
        delete m_instance;
        m_instance = 0;
    }

private:
    TerminalUUIDUtil();
    ~TerminalUUIDUtil();
    static TerminalUUIDUtil* m_instance;
public:
    void init();
    /**
     * @brief setTerminalUUID    更改中心服务器固定码
     * @param uuid
     */
    void updateTerminalUUID(const quint64 &uuid);
    /**
     * @brief getTerminalUUID   获取中心服务器固定码
     * @return
     */
    quint64 getTerminalUUID() const;

    /**
     * @brief getTerminalUUIDType 获取给定固定码所属的客户端类型
     * @param UUID
     * @return
     */
    quint8 getTerminalUUIDType(const quint64 &UUID);

    /**
     * @brief parseTerminalUUID 解析固定码元数据UUID为指定格式Equip_Info
     * @param uuid  固定码
     * @param equipInfo 固定码元数据结构
     */
    void parseTerminalUUID(const quint64 &uuid,Equip_Info *equipInfo = new Equip_Info);
    /**
     * @brief genTerminalUUID   使格式Equip_Info固定码生成quint64固定码UUID
     * @param equipInfo 固定码元数据结构
     * @param descUUID  生成的固定码
     */
    void genTerminalUUID(const Equip_Info &equipInfo,quint64 &descUUID);

private:
    quint64 m_centerUUID;
    QMutex mutex;
};

#endif // TERMINALUUIDUTIL_H
