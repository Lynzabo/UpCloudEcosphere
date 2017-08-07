#ifndef COMMONFILESEXECSTATUS_H
#define COMMONFILESEXECSTATUS_H

#include "taskinfo.h"
#include "resultinfo.h"
#include "transmsglib_global.h"

class TRANSMSGLIBSHARED_EXPORT CommonFilesExecStatus : public TaskInfo
{
public:
    CommonFilesExecStatus();
    ~CommonFilesExecStatus();
protected:
    void toXML(QXmlStreamWriter *writer = 0);
    void toEntity(QXmlStreamReader *reader = 0);
public:

    //状态码
    quint8 State;
    //操作策略
    quint16 Strategy;
    //结果描述
    ResultInfo* resultInfo;
};

#endif // COMMONFILESEXECSTATUS_H
