#ifndef ABSTPATH_H
#define ABSTPATH_H
#include <QtCore>
#include "baselib_global.h"
#include "unicode.h"
/**
 * @brief The AbstPath class    设置应用基本目录结构
 */
class BASELIBSHARED_EXPORT AbstPath
{
public:
    AbstPath();

public:
    /**
     * @brief setApplicationRootDir 设置应用根目录
     * @param rootDir
     */
    virtual void setApplicationRootDir(const QString &rootDir) = 0;
    /**
     * @brief root  返回应用的Root路径
     * @return  /隔开
     */
    virtual QString abst();
    /**
     * @brief binAbst  返回bin目录的路径
     * @return  /隔开
     */
    virtual QString binAbst();
    /**
     * @brief binAbst2  返回bin2目录的路径(存放第三方依赖)
     * @return  /隔开
     */
    virtual QString binAbst2();
    /**
     * @brief confAbst  返回conf目录的路径(存放配置信息)
     * @return  /隔开
     */
    virtual QString confAbst();
    /**
     * @brief dataAbst  返回data目录的路径(存放基础数据)
     * @return  /隔开
     */
    virtual QString dataAbst();

    /**
     * @brief profileAbst 返回profile目录的路径(存放固定码UUID)
     * @return /隔开
     */
    virtual QString profileAbst();

    /**
     * @brief cryAbst   返回cry目录的路径(存放公私钥)
     * @return /隔开
     */
    virtual QString cryAbst();
    /**
     * @brief logAbst  返回log目录的路径(存放日志数据)
     * @return  /隔开
     */
    virtual QString logAbst();
    /**
     * @brief tmpAbst  返回tmp目录的路径(临时数据目录)
     * @return  /隔开
     */
    virtual QString tmpAbst();
protected:
    //应用根目录
    QString rootDir;
};

#endif // ABSTPATH_H
