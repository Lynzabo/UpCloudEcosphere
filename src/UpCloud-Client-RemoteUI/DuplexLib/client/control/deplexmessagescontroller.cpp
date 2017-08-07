#include "deplexmessagescontroller.h"
SINGLETON_INITIALIZE(DeplexMessagesController)
DeplexMessagesController::DeplexMessagesController()
{
    clearSenders();
    clearResults();
    clearQueues();
    senderMutex = new QMutex;
    resultMutex = new QMutex;
}
DeplexMessagesController::~DeplexMessagesController()
{
    clearSenders();
    clearResults();
    clearQueues();
    delete senderMutex;
    senderMutex = NULL;
    delete resultMutex;
    resultMutex = NULL;
}



void DeplexMessagesController::pushSender2MQ(DPSender *sender, const DeplexDefs::Priority priority)
{
    QMutexLocker senderLocker(senderMutex);
    //未使用变量,防止编译时警告,使用Q_UNUSED扩住
    Q_UNUSED(senderLocker)
    enSenderQueue(sender,priority);
}

DPResult *DeplexMessagesController::pullResultFromMQ(DPSender *sender, const DeplexDefs::Priority priority, bool isValid)
{
    QMutexLocker resultLocker(resultMutex);
    //未使用变量,防止编译时警告,使用Q_UNUSED扩住
    Q_UNUSED(resultLocker)
    QString curUUID;
    getSenderUUID(sender,priority,curUUID);
    //可能超时了
    if(curUUID.isEmpty())
    {
        isValid = false;
        return NULL;
    }
    return deResultQueue(curUUID,priority);
}

DPSender *DeplexMessagesController::pullSenderFromMQ()
{
    QMutexLocker senderLocker(senderMutex);
    //未使用变量,防止编译时警告,使用Q_UNUSED扩住
    Q_UNUSED(senderLocker)
    DPSender *sender = 0;
    if(tmpHighSenderQueue.size()>0)
        sender = tmpHighSenderQueue.dequeue();
    else if(tmpNormalSenderQueue.size()>0)
        sender = tmpNormalSenderQueue.dequeue();
    else if(tmpLowSenderQueue.size()>0)
        sender = tmpLowSenderQueue.dequeue();
    return sender;
}

void DeplexMessagesController::destorySender(DPSender *sender, const DeplexDefs::Priority priority)
{
    QString curUUID;
    getSenderUUID(sender,priority,curUUID);
    switch (priority) {
    case DeplexDefs::HighPriority:
        highSenders.remove(sender);
        highResults.remove(curUUID);
        break;
    case DeplexDefs::NormalPriority:
        normalSenders.remove(sender);
        normalResults.remove(curUUID);
        break;
    case DeplexDefs::LowPriority:
        lowSenders.remove(sender);
        lowResults.remove(curUUID);
        break;
    default:
        break;
    }
}

void DeplexMessagesController::pushResult2MQ(RespRemoteUIOperaCentorInfo *rspRemoteUIOperaCentorInfo)
{
    QMutexLocker resultLocker(resultMutex);
    //未使用变量,防止编译时警告,使用Q_UNUSED扩住
    Q_UNUSED(resultLocker)
    using namespace Environment::Datagram::UI_Ctrl;
    QString uuid = trs("%1%2%3").arg(rspRemoteUIOperaCentorInfo->ExecType).arg(TransSeparator).arg(rspRemoteUIOperaCentorInfo->Params);
    QString md5uuid;md5uuid.clear();
    //将字符串生成md5字符串
    MdUtil::getInstance().toMd5(uuid,md5uuid);
    DeplexDefs::Priority priority;
    getSenderPriority(md5uuid,priority);
    DPResult *result = new DPResult(priority,rspRemoteUIOperaCentorInfo->ExecType,rspRemoteUIOperaCentorInfo->Params,
                                    rspRemoteUIOperaCentorInfo->State,rspRemoteUIOperaCentorInfo->Content);
    enResultQueue(md5uuid,result,priority);
}

void DeplexMessagesController::getSenderPriority(const QString &md5uuid, DeplexDefs::Priority &priority)
{
    if(highSenders.values().contains(md5uuid))
    {
        priority = DeplexDefs::HighPriority;
    }
    else if(normalSenders.values().contains(md5uuid))
    {
        priority = DeplexDefs::NormalPriority;
    }
    else if(lowSenders.values().contains(md5uuid))
    {
        priority = DeplexDefs::LowPriority;
    }
}

void DeplexMessagesController::enResultQueue(const QString &md5Uuid, DPResult *result, const DeplexDefs::Priority priority)
{
    switch (priority) {
    case DeplexDefs::HighPriority:
        highResults.insert(md5Uuid,result);
        break;
    case DeplexDefs::NormalPriority:
        normalResults.insert(md5Uuid,result);
        break;
    case DeplexDefs::LowPriority:
        lowResults.insert(md5Uuid,result);
        break;
    default:
        break;
    }
}

void DeplexMessagesController::enSenderQueue(DPSender *sender, const DeplexDefs::Priority priority)
{
    using namespace Environment::Datagram::UI_Ctrl;
    QString uuid = trs("%1%2%3").arg(sender->getExecType()).arg(TransSeparator).arg(sender->getParams());
    QString md5uuid;md5uuid.clear();
//    UuidUtil::nextUUID(uuid);
    //将字符串生成md5字符串
    MdUtil::getInstance().toMd5(uuid,md5uuid);
    switch (priority) {
    case DeplexDefs::HighPriority:
        highSenders.insert(sender,md5uuid);
        tmpHighSenderQueue.enqueue(sender);
        break;
    case DeplexDefs::NormalPriority:
        normalSenders.insert(sender,md5uuid);
        tmpNormalSenderQueue.enqueue(sender);
        break;
    case DeplexDefs::LowPriority:
        lowSenders.insert(sender,md5uuid);
        tmpLowSenderQueue.enqueue(sender);
        break;
    default:
        break;
    }
}

DPResult *DeplexMessagesController::deResultQueue(const QString &senderUUID, const DeplexDefs::Priority priority)
{
    DPResult *resultset = 0;
    switch (priority) {
    case DeplexDefs::HighPriority:
        resultset = highResults.value(senderUUID);
        break;
    case DeplexDefs::NormalPriority:
        resultset = normalResults.value(senderUUID);
        break;
    case DeplexDefs::LowPriority:
        resultset = lowResults.value(senderUUID);
        break;
    default:
        break;
    }
    return resultset;
}

void DeplexMessagesController::clearSenders()
{
    highSenders.clear();
    normalSenders.clear();
    lowSenders.clear();
}

void DeplexMessagesController::clearResults()
{
    qDeleteAll(highResults);
    highResults.clear();
    qDeleteAll(normalResults);
    normalResults.clear();
    qDeleteAll(lowResults);
    lowResults.clear();
}

void DeplexMessagesController::clearQueues()
{
    qDeleteAll(tmpHighSenderQueue);
    tmpHighSenderQueue.clear();
    qDeleteAll(tmpNormalSenderQueue);
    tmpNormalSenderQueue.clear();
    qDeleteAll(tmpLowSenderQueue);
    tmpLowSenderQueue.clear();
}

void DeplexMessagesController::getSenderUUID(DPSender *sender, const DeplexDefs::Priority priority, QString &uuid)
{
    switch (priority) {
    case DeplexDefs::HighPriority:
        uuid = highSenders.value(sender);
        break;
    case DeplexDefs::NormalPriority:
        uuid = normalSenders.value(sender);
        break;
    case DeplexDefs::LowPriority:
        uuid = lowSenders.value(sender);
        break;
    default:
        break;
    }
}

