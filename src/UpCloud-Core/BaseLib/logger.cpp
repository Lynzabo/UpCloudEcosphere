#include "logger.h"
#include <iostream>
#include "util/pathutil.h"
#include "filemanager.h"
#include "util/timerutil.h"

namespace Logger {
    namespace DEST_CONSTANT{
        const QString STDOUT = "stdout";
        const QString R = "R";
        const QString STDOUTR = "stdoutR";
    }
    namespace LEVEL_CONSTANT{
        const QString DEBUG = "Debug";
        const QString WARNING = "Warning";
        const QString CRITICAL = "Critical";
        const QString FATAL = "Fatal";
    }
    QString Logpath = QString();
}

using namespace Logger;
QMutex* LogInterceptor::m_mutex = new QMutex(QMutex::Recursive);
LogInterceptor::LogInterceptor()
    : m_buffer(new QBuffer())
{
    connect(m_buffer, SIGNAL(readyRead()), SLOT(on_buffer_readRead()));
}

LogInterceptor::~LogInterceptor()
{
    m_buffer->deleteLater();
    delete m_mutex;
}

LogInterceptor *LogInterceptor::logInterceptor()
{
    static LogInterceptor interceptor;
    return &interceptor;
}

void LogInterceptor::registerSystemLogger(const QString &tlogpath)
{
    Logger::Logpath = tlogpath;
#ifdef Q_OS_WIN
#ifdef _DEBUG   //Windows环境使用VS编译器
    qInstallMessageHandler(debMsgOutput);
#else
    qInstallMessageHandler(relMsgOutput);
#endif
#else
#ifdef QT_NO_DEBUG   //非Windows环境使用mingGW编译器
    qInstallMessageHandler(relMsgOutput);
#else
    qInstallMessageHandler(debMsgOutput);
#endif
#endif
}

void LogInterceptor::relMsgOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    m_mutex->lock();
    Q_UNUSED(context)
    QString dest,level,rFile,curTime;
    quint32 size;
    logInterceptor()->readLoggerConfig(dest,level,rFile, size);
    QString out,txt;
    //当前等级是否需要输出校验
    logInterceptor()->levelSprintf(txt,type,level);

    if(txt.isEmpty())
    {
        m_mutex->unlock();
        return;
    }
    QByteArray localMsg = msg.toLocal8Bit();
    txt.append(localMsg.constData());
    TimerUtil::toString(curTime);
    out.append(curTime).append("   ");
    out.append(txt);
    //日志输出
    logInterceptor()->outputPrintf(out,dest,rFile,type, size);
    m_mutex->unlock();
}
void LogInterceptor::debMsgOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    m_mutex->lock();
    Q_UNUSED(context)
    QString dest,level,rFile,curTime;
    quint32 size;
    logInterceptor()->readLoggerConfig(dest,level,rFile, size);
    QString out,txt;
    //当前等级是否需要输出校验
    logInterceptor()->levelSprintf(txt,type,level);

    if(txt.isEmpty())
    {
        m_mutex->unlock();
        return;
    }
//    txt.append(context.file).append(";");
//    txt.append(context.function).append(";");
//    txt.append(QString("%1").arg(context.line)).append("]   ");
//    txt.append( msg.toUtf8().constData());
    /*
    QByteArray localMsg = msg.toLocal8Bit();
    txt.append(trs("%1 (%2:%3, %4)").arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function));
    TimerUtil::toString(curTime);
    out.append(curTime).append(" ");
    out.append(txt);
    */
    QByteArray localMsg = msg.toLocal8Bit();
    txt.append(trs("%1 (%4)").arg(localMsg.constData()).arg(context.function));
    TimerUtil::toString(curTime);
    out.append(curTime).append(" ");
    out.append(txt);
    //日志输出
    logInterceptor()->outputPrintf(out,dest,rFile,type, size);
    m_mutex->unlock();
}

void LogInterceptor::readLoggerConfig(QString &dest, QString &level, QString &rFile, quint32 &size)
{
    QSettings settings(Logger::Logpath, QSettings::IniFormat);
    dest = settings.value("upCloud.logger.dest").toString();
    level = settings.value("upCloud.logger.level").toString();
    rFile = settings.value("upCloud.logger.R.file").toString();
    size = settings.value("upCloud.logger.size").toUInt();
    if(dest.isEmpty() ||
            !(dest==Logger::DEST_CONSTANT::STDOUT ||
              dest==Logger::DEST_CONSTANT::R ||
              dest==Logger::DEST_CONSTANT::STDOUTR))
        dest.append(trs("stdout"));
    if(level.isEmpty() ||
            !(level==Logger::LEVEL_CONSTANT::DEBUG ||
              level==Logger::LEVEL_CONSTANT::WARNING ||
              level==Logger::LEVEL_CONSTANT::CRITICAL ||
              level==Logger::LEVEL_CONSTANT::FATAL))
        level.append(trs("Critical"));
    if(rFile.isEmpty())
        rFile.append(trs("runtime.log"));
}
void LogInterceptor::outputPrintf(const QString &out,const QString &dest, const QString &rFile, const QtMsgType &type, const quint32 size)
{
    if((dest==Logger::DEST_CONSTANT::STDOUT || dest==Logger::DEST_CONSTANT::STDOUTR))
        std::cout << qPrintable(out) << std::endl;
    if((dest==Logger::DEST_CONSTANT::R || dest==Logger::DEST_CONSTANT::STDOUTR))
    {
        //        QString logAbst = AbstPath::logAbst();
        QDir dir = QDir(PathUtil::getInstance().executeDir());
        dir.cdUp();
        QString logAbst = dir.absolutePath()+trs("/log/");
        FileManager::getInstance()->writeLine(logAbst,rFile,out, size);
    }
    if(type ==QtFatalMsg )
        abort();
}
void LogInterceptor::levelSprintf(QString &txt, const QtMsgType &type, const QString &level)
{
    switch (type) {
    //调试信息提示
    case QtDebugMsg:
        if(level==Logger::LEVEL_CONSTANT::WARNING ||
                level==Logger::LEVEL_CONSTANT::CRITICAL ||
                level==Logger::LEVEL_CONSTANT::FATAL
                )
            goto drpos;
        txt = QString("[DEBUG] ");
        break;
        //一般的warning提示
    case QtWarningMsg:
        if(level==Logger::LEVEL_CONSTANT::CRITICAL ||
                level==Logger::LEVEL_CONSTANT::FATAL
                )
            goto drpos;
        txt = QString("[WARNING]: ");
        break;
        //严重错误提示
    case QtCriticalMsg:
        if(level==Logger::LEVEL_CONSTANT::FATAL)
            goto drpos;
        txt = QString("[CRITICAL]: ");
        break;
        //致命错误提示
    case QtFatalMsg:
        txt = QString("[FATAL]: ");
        //abort();
    }
drpos:
    return;
}




////旧版本
//#include "logger.h"
//#include <iostream>
//#include <QFile>
//#include <QTextStream>
//#include <QDateTime>
//#include <QDebug>
//#include "filemanager.h"
//#include "unicode.h"
//#include "util/pathutil.h"
//void Logger::readLoggerConfig(QString &dest, QString &level, QString &rFile, quint32 &size)
//{
//    QSettings settings(Logger::Logpath, QSettings::IniFormat);
//    dest = settings.value("upCloud.logger.dest").toString();
//    level = settings.value("upCloud.logger.level").toString();
//    rFile = settings.value("upCloud.logger.R.file").toString();
//    size = settings.value("upCloud.logger.size").toUInt();
//    if(dest.isEmpty() ||
//            !(dest==Logger::DEST_CONSTANT::STDOUT ||
//             dest==Logger::DEST_CONSTANT::R ||
//             dest==Logger::DEST_CONSTANT::STDOUTR))
//        dest.append(trs("stdout"));
//    if(level.isEmpty() ||
//            !(level==Logger::LEVEL_CONSTANT::DEBUG ||
//             level==Logger::LEVEL_CONSTANT::WARNING ||
//              level==Logger::LEVEL_CONSTANT::CRITICAL ||
//             level==Logger::LEVEL_CONSTANT::FATAL))
//        level.append(trs("Critical"));
//    if(rFile.isEmpty())
//        rFile.append(trs("runtime.log"));
//}
//void Logger::levelSprintf(QString &txt, const QtMsgType &type,const QString &level)
//{
//    switch (type) {
//    //调试信息提示
//    case QtDebugMsg:
//        if(level==Logger::LEVEL_CONSTANT::WARNING ||
//                level==Logger::LEVEL_CONSTANT::CRITICAL ||
//                level==Logger::LEVEL_CONSTANT::FATAL
//                )
//            goto drpos;
//        txt = QString("Debug   	");
//        break;
//    //一般的warning提示
//    case QtWarningMsg:
//        if(level==Logger::LEVEL_CONSTANT::CRITICAL ||
//                level==Logger::LEVEL_CONSTANT::FATAL
//                )
//            goto drpos;
//        txt = QString("Warning   	");
//        break;
//    //严重错误提示
//    case QtCriticalMsg:
//        if(level==Logger::LEVEL_CONSTANT::FATAL)
//            goto drpos;
//        txt = QString("Critical   	");
//        break;
//    //致命错误提示
//    case QtFatalMsg:
//        txt = QString("Fatal   	");
//        //abort();
//    }
//    drpos:
//    return;
//}
//void Logger::debMsgOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
//{
//    QString dest,level,rFile;
//    quint32 size;
//    readLoggerConfig(dest,level,rFile, size);
//    QString out,txt;
//    //当前等级是否需要输出校验
//    levelSprintf(txt,type,level);

//    if(txt.isEmpty())
//        return;
//    txt.append(context.file).append(";");;
//    txt.append(context.function).append(";");;
//    txt.append(QString("%1").arg(context.line)).append("]   ");
//    QByteArray localMsg = msg.toLocal8Bit();
//    txt.append(localMsg.constData());
//    out.append(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd")).append("   ");
//    out.append(txt);
//    //日志输出
//    outputPrintf(out,dest,rFile,type, size);
//}


//void Logger::relMsgOutput(QtMsgType type,const QMessageLogContext &context, const QString &msg)
//{
//    QString dest,level,rFile;
//    quint32 size;
//    readLoggerConfig(dest,level,rFile, size);
//    QString out,txt;
//    //当前等级是否需要输出校验
//    levelSprintf(txt,type,level);

//    if(txt.isEmpty())
//        return;
//    QByteArray localMsg = msg.toLocal8Bit();
//    txt.append(localMsg.constData());
//    out.append(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd")).append("   ");
//    out.append(txt);
//    //日志输出
//    outputPrintf(out,dest,rFile,type, size);
//}
//void Logger::outputPrintf(const QString &out,const QString &dest, const QString &rFile, const QtMsgType &type, const quint32 size)
//{
//    if((dest==Logger::DEST_CONSTANT::STDOUT || dest==Logger::DEST_CONSTANT::STDOUTR))
//        std::cout << qPrintable(out) << std::endl;
//    if((dest==Logger::DEST_CONSTANT::R || dest==Logger::DEST_CONSTANT::STDOUTR))
//    {
//        QDir dir = QDir(PathUtil::getInstance().executeDir());
//        dir.cdUp();
//        QString logAbst = dir.absolutePath()+trs("/log/");
//        FileManager::getInstance()->writeLine(logAbst,rFile,out, size);
//    }
//    if(type ==QtFatalMsg )
//        abort();
//}


//void Logger::registerSystemLogger(const QString &logpath)
//{
//    Logger::Logpath = logpath;
//#ifdef Q_OS_WIN
//    #ifdef _DEBUG   //Windows环境使用VS编译器
//        qInstallMessageHandler(Logger::debMsgOutput);
//    #else
//        qInstallMessageHandler(Logger::relMsgOutput);
//    #endif
//#else
//    #ifdef QT_NO_DEBUG   //非Windows环境使用mingGW编译器
//        qInstallMessageHandler(Logger::relMsgOutput);
//    #else
//        qInstallMessageHandler(Logger::debMsgOutput);
//    #endif
//#endif
//}

/**
    调用方式
    //注册系统日志自定义格式监听器
    Logger::registerSystemLogger();
*/

