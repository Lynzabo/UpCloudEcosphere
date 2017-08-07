#ifndef DEPLEXMESSAGESCONTROLLER_H
#define DEPLEXMESSAGESCONTROLLER_H
#include <QtCore>
#include "base.h"
#include "transmsg.h"
#include "client/core/dpsender.h"
#include "client/core/dpresult.h"
#include "client/core/deplexdefs.h"
class DPSender;
class DeplexMessagesController
{
    SINGLETON(DeplexMessagesController)
public:
    /**
     * @brief pushSender2MQ 推发送端入队
     * @param sender
     * @param priority
     */
    void pushSender2MQ(DPSender *sender,const DeplexDefs::Priority priority);
    /**
     * @brief pullSenderFromMQ  从队列中推出发送端
     * @return
     */
    DPSender *pullSenderFromMQ();
    /**
     * @brief destorySender 销毁结果集队列及其发送队列中当前发送端Item
     * @param sender
     * @param priority
     */
    void destorySender(DPSender *sender,const DeplexDefs::Priority priority);
    /**
     * @brief pushResult2MQ    推结果集入队
     * @param rspRemoteUIOperaCentorInfo
     */
    void pushResult2MQ(RespRemoteUIOperaCentorInfo *rspRemoteUIOperaCentorInfo);
    /**
     * @brief pullResultFromMQ   拉发送端的结构集出队
     * @param sender
     * @param priority
     * @return
     */
    DPResult *pullResultFromMQ(DPSender *sender,const DeplexDefs::Priority priority,bool isValid = true);
private:
    /**
     * @brief getSenderPriority 获取发送者优先级
     * @param md5uuid
     * @param priority
     */
    void getSenderPriority(const QString &md5uuid,DeplexDefs::Priority &priority);
    /**
     * @brief enResultQueue 入结果集队列
     * @param result
     * @param priority
     */
    void enResultQueue(const QString &md5Uuid, DPResult *result, const DeplexDefs::Priority priority);
    /**
     * @brief enPdQueue    入发送端队列
     * @param producer
     * @param priority
     */
    void enSenderQueue(DPSender *sender,const DeplexDefs::Priority priority);
    /**
     * @brief deResultQueue   出结果集队列
     * @param senderUUID    发送端唯一标示符
     * @param priority
     * @return
     */
    DPResult *deResultQueue(const QString &senderUUID,const DeplexDefs::Priority priority);
    /**
     * @brief clearSenders  清空所有优先级的发送者
     */
    void clearSenders();
    /**
     * @brief clearResults  清空所有优先级的结构集
     */
    void clearResults();
    /**
     * @brief clearQueues   清空所有队列
     */
    void clearQueues();
    /**
     * @brief getSenderUUID 获取发送者的唯一标示符
     * @param sender
     * @param priority
     * @param uuid  存放发送者唯一标示符
     */
    void getSenderUUID(DPSender *sender,const DeplexDefs::Priority priority,QString &uuid);
private:
    //发送者集合
    QMap<DPSender *,QString> highSenders;
    QMap<DPSender *,QString> normalSenders;
    QMap<DPSender *,QString> lowSenders;
    //结构集集合,key为发送者的value
    QMap<QString,DPResult*> highResults;
    QMap<QString,DPResult*> normalResults;
    QMap<QString,DPResult*> lowResults;
    QMutex *senderMutex;
    QMutex *resultMutex;
    //发送者队列
    QQueue<DPSender *> tmpHighSenderQueue;
    QQueue<DPSender *> tmpNormalSenderQueue;
    QQueue<DPSender *> tmpLowSenderQueue;
};

#endif // DEPLEXMESSAGESCONTROLLER_H
