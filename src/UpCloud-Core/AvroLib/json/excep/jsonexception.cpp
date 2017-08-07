#include "jsonexception.h"

JsonException::JsonException(const QString &_msg):msg(_msg)
{

}
QString JsonException::getMsg() const
{
    return msg;
}


