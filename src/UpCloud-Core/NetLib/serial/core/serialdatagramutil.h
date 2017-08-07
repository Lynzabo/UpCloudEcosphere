#ifndef SERIALDATAGRAMUTIL_H
#define SERIALDATAGRAMUTIL_H

#include "netlib_global.h"
#include <QtCore>
#include "serialdatagraminfo.h"


class NETLIBSHARED_EXPORT SerialDatagramUtil
{
public:
    SerialDatagramUtil();
    /**
     * @brief packDatagram  生成可传输的报文流
     * @param dataIn    当前对象,一般放this指针
     * @param datagram  生成的报文流,使用该流就可以进行传输
     */
    void static packDatagram(quint8 msgType, QByteArray &datagram);

    void static reversalArray(QByteArray& data);
};

#endif // SERIALDATAGRAMUTIL_H
