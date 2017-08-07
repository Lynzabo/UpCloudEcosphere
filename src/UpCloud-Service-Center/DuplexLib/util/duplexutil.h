#ifndef DUPLEXUTIL_H
#define DUPLEXUTIL_H
#include "duplexlib_global.h"
#include "base.h"

class DUPLEXLIBSHARED_EXPORT DuplexUtil
{
public:
    DuplexUtil();
    /**
     * @brief addrIsLegal   校验操作是否存在
     * @param ExecType
     * @return
     */
    static bool addrIsLegal(const quint16 &ExecType);
};

#endif // DUPLEXUTIL_H
