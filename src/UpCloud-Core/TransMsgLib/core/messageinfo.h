#ifndef MESSAGEINFO_H
#define MESSAGEINFO_H
#include "transmsglib_global.h"
#include <QtCore>

class TRANSMSGLIBSHARED_EXPORT MessageInfo
{
public:
    MessageInfo();
    /**
     * @brief messageType   报文类型码
     * @return
     */
    virtual quint8 messageType() const = 0;
};

#endif // MESSAGEINFO_H
