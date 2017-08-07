#ifndef SYSPERMISSION_H
#define SYSPERMISSION_H
#include <QtCore>
#include "base.h"
#include "soalib_global.h"
/**
 * @brief The SysPermission class   连接权限管理系统读取系统权限
 */
class SOALIBSHARED_EXPORT SysPermission
{
    SINGLETON(SysPermission)
public:
    /**
     * @brief getUserName   使用用户主键ID获取用户名称
     * @param userUUID
     * @return
     */
    QString getUserName(const QString userUUID);
    /**
     * @brief getUserUUIDs  使用用户名称模糊获取用户主键列表
     * @param userNames
     * @return
     */
    QList<QString> getUserUUIDs(const QList<QString> userNames);
};

#endif // SYSPERMISSION_H
