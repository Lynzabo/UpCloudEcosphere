#ifndef DPRESULT_H
#define DPRESULT_H

#include <QObject>
#include "duplexlib_global.h"
#include "client/core/deplexdefs.h"
class DUPLEXLIBSHARED_EXPORT DPResult
{
public:

    explicit DPResult(const DeplexDefs::Priority &sMPriority,const quint16 &sExecType,const QString &sParams,const quint8 &rState,const QString &rContent);

    DeplexDefs::Priority getSMPriority() const;

    quint16 getSExecType() const;

    QString getSParams() const;

    quint8 getRState() const;

    QString getRContent() const;
    void setRContent(const QString &value);

    void setRState(const quint8 &value);

private:
    //请求信息

    //请求优先级
    DeplexDefs::Priority sMPriority;
    //操作类型码
    quint16 sExecType;
    //操作参数
    QString sParams;
    //结果信息
    //状态码
    quint8 rState;
    //返回内容
    QString rContent;
};

#endif // DPRESULT_H
