#ifndef UUIDUTIL_H
#define UUIDUTIL_H
#include <QtCore>
#include "baselib_global.h"
/**
 * @brief The UuidUtil class    标准随机码生成工具
 */
class BASELIBSHARED_EXPORT UuidUtil
{
public:
    enum TYPE
    {
        BASIC,//621229FA7117066DF3B50814A9FF5D81
        COMMON,//621229FA-7117-066D-F3B5-0814A9FF5D81
        ADVANCED//{621229FA-7117-066D-F3B5-0814A9FF5D81}
    };
    /**
     * @brief nextUUID  生成随机字符串
     * @param _uuid 存放生成随机字符串
     * @param tp    是否去掉符号[{}-]
     */
    static void nextUUID(QString &_uuid,UuidUtil::TYPE tp = UuidUtil::BASIC);
};

#endif // UUIDUTIL_H
