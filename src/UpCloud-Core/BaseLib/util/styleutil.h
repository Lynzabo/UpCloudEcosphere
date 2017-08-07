#ifndef STYLEUTIL_H
#define STYLEUTIL_H
#include "core/singleton.h"
#include "baselib_global.h"

/**
 * @brief The StyleUtil class   样式主题设置
 */
class BASELIBSHARED_EXPORT StyleUtil
{
    SINGLETON(StyleUtil)
public:
    void setStyleSheet(const QString styles);
};

#endif // STYLEUTIL_H
