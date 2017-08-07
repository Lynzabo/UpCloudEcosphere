#include "abstpath.h"

AbstPath::AbstPath()
{
    rootDir.clear();
}

QString AbstPath::abst()
{
    if(rootDir.isEmpty())
        throw trs("应用根目录不存在");
    return QString("%1/").arg(rootDir);
}

QString AbstPath::binAbst()
{
    return QString("%1%2/").arg(abst()).arg("bin");
}

QString AbstPath::binAbst2()
{
    return QString("%1%2/").arg(abst()).arg("bin2");
}

QString AbstPath::confAbst()
{
    return QString("%1%2/").arg(abst()).arg("conf");
}

QString AbstPath::dataAbst()
{
    return QString("%1%2/").arg(abst()).arg("data");
}

QString AbstPath::profileAbst()
{
    return QString("%1%2/%3/").arg(abst()).arg("data").arg("profile");
}

QString AbstPath::cryAbst()
{
    return QString("%1%2/%3/").arg(abst()).arg("data").arg("cry");
}

QString AbstPath::logAbst()
{
    return QString("%1%2/").arg(abst()).arg("log");
}

QString AbstPath::tmpAbst()
{
    return QString("%1%2/").arg(abst()).arg("tmp");
}

