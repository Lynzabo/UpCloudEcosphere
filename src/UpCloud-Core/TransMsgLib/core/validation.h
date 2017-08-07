#ifndef VALIDATION_H
#define VALIDATION_H

#include "transmsglib_global.h"
#include "err/transexception.h"
#include <QtCore>
//报文元数据校验基本模板(4个)
#define COMMON_VALIDATE(excep,dataGramType)                                                          \
    /*报文类型为空*/                                                                      \
    if(this->MessageType==0)                                                            \
    {                                                                                   \
        excep.setType(Environment::Datagram::State::_2);                                \
        excep.setText(Environment::Datagram::State::_2_DESC_DatagramTypeIsNull);        \
        throw excep;                                                                    \
    }                                                                                   \
    /*报文类型不匹配 */                                                                   \
    if(this->MessageType!=dataGramType)                           \
    {                                                                                   \
        excep.setType(Environment::Datagram::State::_3);                                \
        excep.setText(Environment::Datagram::State::_3_DESC_DatagramUnmatched);         \
        throw excep;                                                                    \
    }                                                                                   \
    /*固定码为空 */                                                                       \
    if(this->UUID==0)                                                                   \
    {                                                                                   \
        excep.setType(Environment::Datagram::State::_4);                                \
        excep.setText(Environment::Datagram::State::_4_DESC_UUIDIsNull);                \
        throw excep;                                                                    \
    }                                                                                   \
    /*请求码为空 */                                                                       \
    if(this->RequestID.isEmpty())                                                       \
    {                                                                                   \
        excep.setType(Environment::Datagram::State::_5);                                \
        excep.setText(Environment::Datagram::State::_5_DESC_RequestIDIsNull);           \
        throw excep;                                                                    \
    }
//任务报文元数据校验模板(6个)
#define TASK_VALIDATE(excep,dataGramType)                                                            \
    COMMON_VALIDATE(excep,dataGramType)                                                              \
    /*任务编号为空*/                                                                       \
    if(this->TaskUUID == 0)                                                             \
    {                                                                                   \
        excep.setType(Environment::Datagram::State::_6);                                \
        excep.setText(Environment::Datagram::State::_6_DESC_TaskNumIsNull);             \
        throw excep;                                                                    \
    }                                                                                   \
    /*执行策略为空*/                                                                      \
    if(this->Strategy == 0)                                                             \
    {                                                                                   \
        excep.setType(Environment::Datagram::State::_7);                                \
        excep.setText(Environment::Datagram::State::_7_DESC_StrategyIsNull);            \
        throw excep;                                                                    \
    }
class TRANSMSGLIBSHARED_EXPORT Validation
{
public:
    Validation();
public:
    /**
     * @brief validate  校验当前实体合法性
     * 使用场景:
     *  1.在拼装报文前自定义校验语法校验
     *  2.在解析报文成实体以后,自定义校验实体语法校验,不用关心解析xml出错,因为QXmlStreamReader::hasError()会自动接住错误,
     *  详细看ReqUnstructFilesDownloadInfo::toEntity()接口
     */
    virtual void validate(TransException &excep) = 0;
};

#endif // VALIDATION_H
