#include <QCoreApplication>
#include "util/computerinfo.h"
int main(int argc, char *argv[])
{
    QCoreApplication app( argc, argv );
    ComputerInfo::getInstance().numberOfProcessors();
    ComputerInfo::getInstance().release();
    return app.exec();
}
/*
#include "base.h"
int main(int argc, char *argv[])
{
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();

    QCoreApplication app( argc, argv );
    qDebug() << trs("说三道四");
    qWarning() << trs("说三道A");
    qCritical() << trs("说三道四");
    return app.exec();
}
*/
