#ifndef RUABSTPATH_H
#define RUABSTPATH_H
#include "base.h"
#include "baseiremotelib_global.h"

/**
 * @brief The CSAbstPath class  远程UI目录结构
 */
class BASEIREMOTELIBSHARED_EXPORT RUAbstPath : public AbstPath
{
    SINGLETON(RUAbstPath)
public:
    /**
     * @brief setApplicationRootDir 设置应用根目录
     * @param rootDir
     */
    virtual void setApplicationRootDir(const QString &rootDir);
};

#endif // RUABSTPATH_H
