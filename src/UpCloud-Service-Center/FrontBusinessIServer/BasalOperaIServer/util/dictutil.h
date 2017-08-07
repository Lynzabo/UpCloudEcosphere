#ifndef DICTUTIL_H
#define DICTUTIL_H
#include <QtCore>
#include "../../../BusinessIServer/BasalIServer/bean/csdict.h"
#include "avro.h"
#include <QList>
class DictUtil
{
public:
    DictUtil();
    /**
     * @brief taskEntinyFromjsonStr 将任务实体json串转化实体对象
     * @param task
     * @param msg
     * @param num
     * @return
     */
    static bool taskEntinyFromjsonStr(QList<CsDict>&  task, const QString& msg);
    /**
     * @brief taskEntinyFromjsonStr 将任务实体json串转化实体对象
     * @param task
     * @param msg
     * @return
     */
    static bool taskEntinyFromjsonStr(CsDict& task,const QString& msg);
    /**
     * @brief taskEntinyTojsonStr 将任务实体对象转化json串
     * @param msg
     * @param task
     * @param num
     */
    static void taskEntinyTojsonStr(QString& msg, const QList<CsDict>&  dictList);
    /**
     * @brief taskEntinyTojsonStr  将任务实体对象转化json串
     * @param msg
     * @param task
     */
    static void taskEntinyTojsonStr(QString& msg,const CsDict& task);


};

#endif // DICTUTIL_H
