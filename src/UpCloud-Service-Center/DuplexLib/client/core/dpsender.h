#ifndef DPSENDER_H
#define DPSENDER_H

#include <QtCore>
#include "duplexlib_global.h"
#include "dpresult.h"
#include "avro.h"
#include "client/control/deplexmessagescontroller.h"
#include "client/core/deplexdefs.h"
#define PERMANENT_SURVIVAL  -1

class DUPLEXLIBSHARED_EXPORT DPSender
{
public:
    explicit DPSender();
public:
    /**
     * @brief setExpiredTime    设置请求过期时间
     * @param millisecond   <0代表永久存活,
     */
    void setExpiredTime(int millisecond = PERMANENT_SURVIVAL);
    /**
     * @brief doSendBySync  同步获取结果集
     * @param priority
     * @return
     */
    DPResult *doSendBySync(const DeplexDefs::Priority priority = DeplexDefs::NormalPriority);
    /**
     * @brief destory   销毁发送端及发送端所在队列中结果集和发送队列中当前发送端Item
     */
    void destory();
    quint16 getExecType() const;
    /**
     * @brief setExecType   设置操作类型
     * @param value
     */
    void setExecType(const quint16 &value);

    QString getParams() const;
    /**
     * @brief setParams 设置请求参数
     * @param value
     */
    void setParams(const QString &value);

private:
    DeplexDefs::Priority mPriority;
    //操作类型码
    quint16 execType;
    //操作参数
    QString params;
};

#endif // DPSENDER_H
