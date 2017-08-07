#include "pushcontext.h"

PushContext::PushContext(QObject *parent) : QObject(parent)
{
    socks.clear();
    message = NULL;
}

PushContext::~PushContext()
{
    socks.clear();
    delete message;
    message = NULL;
}
QVector<quint64> PushContext::getSocks() const
{
    return socks;
}

void PushContext::setSocks(const QVector<quint64> &value)
{
    socks = value;
}
MessageInfo *PushContext::getMessage() const
{
    return message;
}

void PushContext::setMessage(MessageInfo *value)
{
    message = value;
}
