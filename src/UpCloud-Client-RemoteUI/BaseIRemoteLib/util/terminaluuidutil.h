#ifndef TERMINALUUIDUTIL_H
#define TERMINALUUIDUTIL_H

#include "base.h"
#include "transmsg.h"
#include "ruabstpath.h"
#include "baseiremotelib_global.h"
/**
 * @brief The TerminalUUIDUtil class    终端固定码生成更新工具类
 */
class  BASEIREMOTELIBSHARED_EXPORT TerminalUUIDUtil
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
     * @brief genUUID   初始化客户端UUID
     * @param profileName
     * 操作:
     * 当ClientType为DESKTOP_REMOTEUI或J2EE_REMOTEUI,判断当前profile文件是否存在,
     *  如果不存在,新产生该文件,并缓存该UUID到TerminalUUID属性中
     *  如果存在,校验是否可以获取到固定码元数据,
     *      如果获取不到,新生成UUID到profile文件,并再次缓存该UUID到TerminalUUID属性中
     *      若能获取到,缓存该UUID到TerminalUUID属性中
     * 当ClientType为DESKTOP_NODER,判断当前profile文件是否存在,
     *  如果不存在,间隔50ms循环判断文件是否存在,"
     *  如果存在,校验是否可以获取到固定码元数据,
     *      如果获取不到,抛异常出去
     *      如果获取到,缓存该UUID到TerminalUUID属性中
     */
    /**
     * @brief setTerminalUUID    更改固定码
     * @param uuid
     */
    void updateTerminalUUID(const QString &uuid);
    /**
     * @brief getTerminalUUID   获取固定码
     * @return
     */
    quint64 getTerminalUUID() const;
    /**
     * @brief validateTerminalUUID  校验固定码是否合法
     * @param UUID
     * @return
     */
    bool validateTerminalUUID(const quint64 &UUID);

    /**
     * @brief parseTerminalUUID 解析固定码元数据
     * @param uuid  固定码
     * @param equipInfo 固定码元数据结构
     */
    void parseTerminalUUID(const quint64 &uuid,Equip_Info *equipInfo = new Equip_Info);
    /**
     * @brief genTerminalUUID   适用固定吗元数据生成固定码
     * @param equipInfo 固定码元数据结构
     * @param descUUID  生成的固定码
     */
    void genTerminalUUID(const Equip_Info &equipInfo,quint64 &descUUID);

private:
    bool validateTerminalUUID(const Equip_Info* equipInfo);
    void createTerminalUUID(Equip_Info* equipInfo);

private:
    quint64 terminalUUID;
    QMutex mutex;
};

#endif // TERMINALUUIDUTIL_H
