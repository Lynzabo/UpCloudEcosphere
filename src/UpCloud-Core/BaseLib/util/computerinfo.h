#ifndef COMPUTERINFO_H
#define COMPUTERINFO_H
#include <QtCore>
#include "baselib_global.h"
#include "core/singleton.h"
/**
 * @brief The ComputerInfo class 读取电脑信息
 * 包括硬件各参数信息,及多网卡信息，主机名等等
 */
class BASELIBSHARED_EXPORT ComputerInfo
{
    // 使用上云单例模式:
    // 取得对象 ComputerInfo::getInstance()
    // 删除对象 ComputerInfo::release()
    SINGLETON(ComputerInfo)

public:
    /**
     * @brief ProcessorType 获取CPU型号
     * @return
     */
    QString ProcessorType();
    /**
     * @brief numberOfProcessors    获取CPU数量
     * @return
     */
    quint8 numberOfProcessors();



    /**
     * @brief hostName  获得主机名称
     * @return
     */
    QString hostName();

};

#endif // COMPUTERINFO_H
