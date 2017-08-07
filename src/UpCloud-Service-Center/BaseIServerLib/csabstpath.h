#ifndef CSABSTPATH_H
#define CSABSTPATH_H
#include "base.h"
#include "baseiserverlib_global.h"
/**
 * @brief The CSAbstPath class  中心服务器目录结构
 */
class BASEISERVERLIBSHARED_EXPORT CSAbstPath : public AbstPath
{
    SINGLETON(CSAbstPath)
public:
    /**
     * @brief setApplicationRootDir 设置应用根目录
     * @param rootDir
     */
    virtual void setApplicationRootDir(const QString &rootDir);
};

#endif // CSABSTPATH_H
