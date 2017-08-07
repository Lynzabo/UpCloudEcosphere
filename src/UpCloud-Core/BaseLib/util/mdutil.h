#ifndef MDUTIL_H
#define MDUTIL_H
#include "core/singleton.h"
#include "baselib_global.h"
#include <QtCore>

/**
 * @brief The Md5Util class md5工具类
 */
class BASELIBSHARED_EXPORT MdUtil
{
    SINGLETON(MdUtil)
public:
    /**
     * @brief toMd5 将原字符串转换成md5 32位字符串
     * @param src
     * @param md5desc
     */
    void toMd5(const QString &src,QString &md5desc);
};

#endif // MD5UTIL_H
