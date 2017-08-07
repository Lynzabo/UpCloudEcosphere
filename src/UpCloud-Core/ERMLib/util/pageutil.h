#ifndef PAGEUTIL_H
#define PAGEUTIL_H
#include <QtCore>
#include "ermlib_global.h"
#include "erm.h"

/**
 * @brief The PageUtil class    分页组装工具类
 */
class ERMLIBSHARED_EXPORT PageUtil
{
public:
    PageUtil();
    /**
     * @brief pageEntityFromjsonStr 将Page实体json串转换为page实体对象
     * @param msg   json串
     * @param page  要转换的page对象
     * @param resultStr 结果集json串
     * @return
     */
    static bool pageEntityFromjsonStr(const QString &msg,Page &page,QString &resultStr = QString(""));
    /**
     * @brief pageEntityTojsonStr   将page实体对象拼装为json串
     * @param page  page对象
     * @param resultStr   结果集json串
     * @param msg   拼装的json串
     */
    static void pageEntityTojsonStr(const Page &page,const QString &resultStr,QString &msg);
};

#endif // PAGEUTIL_H
