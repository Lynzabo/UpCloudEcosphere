#include "dpsender.h"
using QtJson::JsonObject;
using QtJson::JsonArray;
using namespace Environment::Duplex_Interaction;
DPSender::DPSender()
{
    this->mPriority = DeplexDefs::Priority::NormalPriority;
    this->execType = (quint16)0;
    this->params.clear();
}

void DPSender::setExpiredTime(int millisecond)
{
    Q_UNUSED(millisecond)
    //TODO  待实现
}

DPResult *DPSender::doSendBySync(const DeplexDefs::Priority priority)
{
    mPriority = priority;
    //让发送者入队
    DeplexMessagesController::getInstance().pushSender2MQ(this,priority);
    //pullResultWaitForMQ   阻塞获取结果集
    {
        //返回结构集
        DPResult *resultSet = 0;bool isValid = true;
        while(1)
        {
            resultSet = DeplexMessagesController::getInstance().pullResultFromMQ(this,priority,isValid);
            //超时
            if(!isValid&&!resultSet)
                goto end;
            //获取到结果集
            if(resultSet)
                goto end;
            QThread::msleep(20);
        }
        end:;
        if(resultSet)
        {
            bool ok;
            JsonObject jsonResult = QtJson::parse(resultSet->getRContent(),ok).toMap();
            if(!ok) {
                qDebug() << Data_Authority::_8_DESC_ParseDataError;
                resultSet->setRState(Data_Authority::_8);
                resultSet->setRContent(Data_Authority::_8_DESC_ParseDataError);
            }
            else
            {
                QString content = jsonResult["content"].toString();
                resultSet->setRContent(content);
            }

        }
        return resultSet;
    }
}

void DPSender::destory()
{
    //销毁结果集队列及其发送队列中当前发送端Item
    DeplexMessagesController::getInstance().destorySender(this,mPriority);
    delete this;
}
quint16 DPSender::getExecType() const
{
    return execType;
}

void DPSender::setExecType(const quint16 &value)
{
    execType = value;
}
QString DPSender::getParams() const
{
    return params;
}

void DPSender::setParams(const QString &value)
{
    params = value;
}



