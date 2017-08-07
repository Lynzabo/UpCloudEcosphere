#include "binary.h"

Binary::Binary():uBIOInputStream(&uBIOdata, QIODevice::WriteOnly),uBIOOutputStream(&uBIOdata, QIODevice::ReadOnly)
{
    uBIOdata.clear();
    uBIOInputStream.setVersion(QDataStream::Qt_4_3);
    uBIOOutputStream.setVersion(QDataStream::Qt_4_3);
}

Binary::~Binary()
{
}

QByteArray &Binary::toDataStream()
{
    return uBIOdata;
}

void Binary::fromDataStream(const QByteArray &out)
{
    uBIOdata.clear();
    uBIOdata = out;
}

