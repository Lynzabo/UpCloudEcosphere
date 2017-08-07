#ifndef ERRORINFO_H
#define ERRORINFO_H

#include "result.h"
#include "core/serializable.h"

class TRANSMSGLIBSHARED_EXPORT ResultInfo : public Serializable
{
    friend class CommonFilesExecStatus;
public:
    ResultInfo();
    ~ResultInfo();
protected:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
public:
    //存放一组结果信息
    QVector<Result*> results;
};

#endif // ERRORINFO_H
