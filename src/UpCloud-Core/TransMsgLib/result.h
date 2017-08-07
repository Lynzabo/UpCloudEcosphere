#ifndef ERROR_H
#define ERROR_H
#include "base.h"
#include "transmsglib_global.h"
#include "core/serializable.h"

class TRANSMSGLIBSHARED_EXPORT Result : public Serializable
{
    friend class ResultInfo;
public:
    Result();
protected:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
public:
    //文件下载地址
    QString DownloadURLs;
    //返回信息
    QString backMsg;
};

#endif // ERROR_H
