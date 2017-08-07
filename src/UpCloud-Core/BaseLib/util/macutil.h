#ifndef MACUTIL_H
#define MACUTIL_H

#include <QtCore>

#include "baselib_global.h"

class BASELIBSHARED_EXPORT MACUtil
{
public:
    MACUtil();

    /**
     * @brief getAllMAC 获取本机所有的MAC地址
     * @param AllMACAddrs   所有的MAC地址
     */
    static void getAllMAC(QStringList& AllMACAddrs);
    /**
     * @brief getActiveMAC  获取本机所有激活状态的MAC地址
     * @param ActiveMACAddrs    所有激活状态的MAC地址
     */
    static void getActiveMAC(QStringList& ActiveMACAddrs);
};

#endif // MACUTIL_H
