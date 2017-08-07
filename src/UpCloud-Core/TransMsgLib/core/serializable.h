#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H
#include "transmsglib_global.h"
#include <QtCore>
class TRANSMSGLIBSHARED_EXPORT Serializable
{
public:
    Serializable();
public:
    /**
     * @brief toXML 序列化
     * @param writer
     */
    virtual void toXML(QXmlStreamWriter *writer = 0) = 0;
    /**
     * @brief toEntity  反序列化
     * @return
     */
    virtual void toEntity(QXmlStreamReader *reader = 0) = 0;
};

#endif // SERIALIZABLE_H
