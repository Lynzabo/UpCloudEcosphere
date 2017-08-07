#ifndef BINARY_H
#define BINARY_H
#include <QtCore>
#include "avrolib_global.h"
class AVROLIBSHARED_EXPORT Binary
{
public:
    Binary();
    ~Binary();
public:
    /**
     * @brief toDataStream  转换对象为数据流
     * @param in
     */
    virtual QByteArray &toDataStream();
    /**
     * @brief fromDataStream    转换数据流为对象
     * @param out
     */
    virtual void fromDataStream(const QByteArray &out);
protected:
    //下面三个属性提供给BInary基类使用
    //输入流
    QDataStream uBIOInputStream;//Upcloud Binary InputputStream
    //数据流
    QByteArray uBIOdata;
    //输入流
    QDataStream uBIOOutputStream;//Upcloud Binary OutputStream
};

#endif // BINARY_H
