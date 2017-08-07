#include "computerinfo.h"
#include <QHostInfo>
SINGLETON_ALL_IN_ONE(ComputerInfo)
#ifdef Q_OS_WIN
// 使用上云单例模式:
// 静态instance对象的初始化 ComputerInfo* cls::instance = 0;
// 生成默认的构造 Class::Class() {}                   \
                Class::~Class() {}
#include "windows.h"
QString ComputerInfo::ProcessorType()
{
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    return QString("%1").arg(info.dwProcessorType);
}

quint8 ComputerInfo::numberOfProcessors()
{
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    return info.dwNumberOfProcessors;
}

QString ComputerInfo::hostName()
{
    QString localHostName = QHostInfo::localHostName();
    return localHostName;
}
#else
QString ComputerInfo::ProcessorType()
{
//    SYSTEM_INFO info;
//    GetSystemInfo(&info);
//    return QString("%1").arg(info.dwProcessorType);
    //TODO
    return QString("");
}

quint8 ComputerInfo::numberOfProcessors()
{
//    SYSTEM_INFO info;
//    GetSystemInfo(&info);
//    return info.dwNumberOfProcessors;
     //TODO
    return 0;
}

QString ComputerInfo::hostName()
{
    QString localHostName = QHostInfo::localHostName();
    return localHostName;
}
#endif
