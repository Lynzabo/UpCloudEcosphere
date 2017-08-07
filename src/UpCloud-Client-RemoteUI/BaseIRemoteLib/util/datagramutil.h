#ifndef DATAGRAMUTIL_H
#define DATAGRAMUTIL_H
#include <QtCore>
#include "base.h"
#include "ruabstpath.h"
#include "terminaluuidutil.h"
#include "baseiremotelib_global.h"

class BotanEnDecrypt;
/**
 * @brief The DatagramUtil class    报文辅助工具类
 */
class BASEIREMOTELIBSHARED_EXPORT DatagramUtil
{
public:
    static DatagramUtil& getInstance()
    {
        return *m_instance;
    }

    static void release()
    {
        delete m_instance;
        m_instance = 0;
    }

private:
    DatagramUtil();
    ~DatagramUtil();
    static DatagramUtil* m_instance;

public:
    void init();
    /**
         * @brief packDatagram  生成可传输的报文
         * @param dataIn   当前对象,一般放this指针
         * @param datagram  生成的报文流,使用该留就可以进行传输
         * Notice:调用该接口前,不需要指定报文类型,固定码,请求码,系统会自动分配
         */
    void packDatagram(MessageInfo *dataIn, QByteArray &datagram);

    /**
     * @brief parseDatagram 使用报文流生报文实体对象
     * @param CallbackByDatagram    解析报文装帧格式回调
     * @param CallbackByMessage 解析报文体回调
     * @param datagram  报文流
     */
    template<typename T1,typename T2>
    void parseDatagram(void CallbackByDatagram(T1 *t1),T2* CallbackByMessage(T2 *t2),QByteArray &datagram)
    {
        //报文类型
        quint8 msgType;
        //报文内容
        QString message;
        //解析报文装帧并存储报文装帧元数据到t1中
        parseGramStream(CallbackByDatagram,datagram,msgType,message);
        //生成报文实体对象并存储报文实体对象到t2中
        parseMessageText(CallbackByMessage,msgType,message);
    }
    /**
     * @brief parseGramStream   转换报文流为实体
     * @param Callback  回调报文装帧数据
     * @param datagram  报文流
     * @param msgType   报文类型,为parseDatagram接口中parseEntity时调用
     * @param condram   报文内容,为parseDatagram接口中parseEntity时调用
     */
    template<typename T>
    void parseGramStream(void Callback(T *t),QByteArray &datagram,quint8 &msgType,QString &message)
    {

        DataGramInfo *gram = new DataGramInfo;
        QBuffer buf(&datagram);
        buf.open(QIODevice::ReadOnly);
        QDataStream in(&buf);
        in.setVersion(QDataStream::Qt_4_7);
        //1.文件开始标记-->2字节
        in >> gram->begin;
        //2.报文类型-->1字节
        in >> gram->msgType;
        //3.固定码-->8字节
        in >> gram->UUID;
        //4.请求码-->32字节
        in >> gram->requestID;
        //5.时间戳-->8字节
        in >> gram->timestamp;
        //6.报文体长度
        in >> gram->dataLength;
        //7.报文体
        in >> gram->message;
        //8.文件结尾标示符-->2字节
        in >> gram->end;
        buf.close();
        //校验报文类型是否合法,不合法直接抛出异常,组织继续后面代码执行
        validateMsgType(gram->msgType);
        msgType = gram->msgType;
        message = gram->message;
        Callback(gram);
    }
    /**
     * @brief validateMsgType  校验报文类型是否合法,不合法直接抛出异常
     * @param msgType
     */
    void validateMsgType(const quint8 &msgType);

    void encrypt();
    /**
     * @brief parseMessageText   使用报文类型和报文体文本反向生报文实体对象
     * @param msgType   报文类型
     * @param condram   报文体文本
     * @param entity    报文实体对象
     * throw TransException
     */
    template<typename T>
    T* parseMessageText(T* Callback(T *t), const quint8 msgType, const QString &condram)
    {
        //继parseGramStream后,再次校验报文类型是否合法,不合法直接抛出异常,组织继续后面代码执行
        Serializable *entity = new T;

        read(msgType,condram,entity);
        return Callback((T*)entity);
    }

    QString m_pubKey;
    QString m_priKey;
private:
    void read(const quint8 msgType, const QString &condram,Serializable *entity);
    /**
     * @brief MessageType  返回报文类型码
     * @param dataIn   当前对象,一般放this指针
     * @param msgType   报文类型码
     */
    void MessageType(MessageInfo *dataIn, quint8 &msgType);
    /**
     * @brief UUID  返回报文固定码
     * @param _uuid 报文固定码
     * 以后换成从协处理器上读取
     */
    void UUID(quint64 &_uuid);
    /**
     * @brief RequestID 生成一个请求码
     * @param _requestID    报文请求码
     */
    void RequestID(QString &_requestID);
    /**
     * @brief Timestamp 生成一个时间戳
     */
    void Timestamp(quint64 &_timestamp);
    /**
     * @brief parseXML  转换数据实体为xml
     * @param dataIn    数据实体
     * @param xml   实体对象XML
     * @param msgType   报文类型
     * @param uuid  固定码
     * @param requestID 请求码
     */
    void parseXML(MessageInfo *dataIn, quint64 &uuid, QString &requestID, QString &xml);
};

#endif // DATAGRAMUTIL_H
