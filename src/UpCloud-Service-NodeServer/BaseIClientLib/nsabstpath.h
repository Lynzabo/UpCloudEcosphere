#ifndef NSABSTPATH_H
#define NSABSTPATH_H
#include "base.h"
#include "baseiclientlib_global.h"
/**
 * @brief The CSAbstPath class  节点服务器目录结构
 */
class BASEICLIENTLIBSHARED_EXPORT NSAbstPath : public AbstPath
{
    SINGLETON(NSAbstPath)

public:
    /**
     * @brief setApplicationRootDir 设置应用根目录
     * @param rootDir
     */
    virtual void setApplicationRootDir(const QString &rootDir);
};

#endif // NSABSTPATH_H
