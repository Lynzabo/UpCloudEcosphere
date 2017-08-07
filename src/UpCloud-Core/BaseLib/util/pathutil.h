#ifndef PATHUTIL_H
#define PATHUTIL_H
#include "core/singleton.h"
#include "baselib_global.h"
/**
 * @brief The PathUtil class    路径读取工具类
 * 其他常用的参考QDir,QFileInfo,QFile
 */
class BASELIBSHARED_EXPORT PathUtil
{
    SINGLETON(PathUtil)
public:
    /**
     * @brief absoluteFilePath  在指定dir目录下查找fileName,返回fileName的绝对路径
     * @param dir
     * @param fileName
     * @return  fileName的绝对路径
     * 注意:
     *  1.Windows/Linux等路径格式都为"/",而不是"\\"
     *  2.当dir目录里不包括fileName,输出dir/fileName
     */
    QString absoluteFilePath(const QString &dir,const QString & fileName) const;
    /**
     * @brief executeDir    返回当前应用所在绝对路径
     * @return
     * 注意:
     *  1.Windows/Linux等路径格式都为"/",而不是"\\"
     */
    QString executeDir();
    /**
     * @brief executePath    返回当前应用主程序所在绝对路径
     * @return
     * 注意:
     *  1.Windows/Linux等路径格式都为"/",而不是"\\"
     */
    QString executePath();
    /**
     * @brief executeName   返回当前应用名称
     * @return
     */
    QString executeName() const;
private:
    /**
     * @brief backslash2Slash   修改路径中所有反斜杠"\\"为斜杠"/"
     * @param strPath
     */
    void backslash2Slash(QString& strPath);
};

#endif // PATHUTIL_H
