#include "uuidutil.h"
#include <quuid.h>

void UuidUtil::nextUUID(QString &_uuid, TYPE tp)
{
    QUuid uuid;
    QString str = uuid.createUuid().toString();
    if(tp == BASIC)
        _uuid = str.remove(QRegExp("[{}-]"));
    else if(tp == COMMON)
        _uuid = str.remove(QRegExp("[{}]"));
    else
        _uuid = str;

}

