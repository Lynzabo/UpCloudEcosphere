#ifndef I18NUTIL_H
#define I18NUTIL_H
#include "core/singleton.h"
#include "baselib_global.h"

/**
 * @brief The I18NUtil class    国际化操作工具类
 */
class BASELIBSHARED_EXPORT I18NUtil
{
    SINGLETON(I18NUtil)
public:
    /**
     * @brief installTranslator 翻译应用
     * @param m_dir  qm文件存放目录
     */
    void installTranslator(const QString & m_dir);
};

#endif // I18NUTIL_H
