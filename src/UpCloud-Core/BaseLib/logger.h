#ifndef LOGGER_H
#define LOGGER_H
#include <QtCore>
#include "unicode.h"
#include "abstpath.h"
#include "baselib_global.h"

class LogInterceptor : public QObject
{
    Q_OBJECT
protected:
    LogInterceptor();
    ~LogInterceptor();
public:
    /**
         * @brief registerSystemLogger  注册系统日志自定义事件
         */
    static void BASELIBSHARED_EXPORT registerSystemLogger(const QString &tlogpath);

private:
    static LogInterceptor* logInterceptor();
    /**
         * @brief relMsgOutput  Release模式输出异常
         * @param type
         * @param msg
         */
    static void relMsgOutput(QtMsgType type,const QMessageLogContext &context, const QString &msg);
    /**
         * @brief debMsgOutput  Debug模式输出异常
         * @param type
         * @param context
         * @param msg
         */
    static void debMsgOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);
    /**
         * @brief readLoggerConfig  读取logger.conf配置文件
         * @param dest
         * @param level
         * @param rFile
         * @param size
         */
    static void readLoggerConfig(QString &dest, QString &level, QString &rFile, quint32 &size);
    /**
         * @brief levelSprintf  等级是否输出校验
         * @param txt
         * @param type
         * @param level
         */
    static void levelSprintf(QString &txt, const QtMsgType &type,const QString &level);
    /**
         * @brief printf    日志输出
         * @param out
         * @param dest
         * @param rFile
         * @param type
         * @param size
         */
    static void outputPrintf(const QString &out, const QString &dest, const QString &rFile, const QtMsgType &type, const quint32 size);
    //待以后向UI传递控制台输出日志时使用
    //begin
private Q_SLOTS:
    void on_buffer_readRead() { emit readyRead(); }
Q_SIGNALS:
    //获取QBuffer输入内容时
    void readyRead();
    //connect(Utils::Logger::logger(), SIGNAL(readyRead()), SLOT(onLogBufferReadyRead()));
    //end
private:
    static QMutex *m_mutex;
    //存放日志缓存
    QBuffer* m_buffer;
};

////旧版本
//namespace Logger{
//    namespace DEST_CONSTANT{
//        const QString STDOUT = "stdout";
//        const QString R = "R";
//        const QString STDOUTR = "stdoutR";
//    }
//    namespace LEVEL_CONSTANT{
//        const QString DEBUG = "Debug";
//        const QString WARNING = "Warning";
//        const QString CRITICAL = "Critical";
//        const QString FATAL = "Fatal";
//    }
//BASELIBSHARED_EXPORT QString Logpath;
///**
// * @brief relMsgOutput  Release模式输出异常
// * @param type
// * @param msg
// */
//void relMsgOutput(QtMsgType type,const QMessageLogContext &context, const QString &msg);
///**
// * @brief debMsgOutput  Debug模式输出异常
// * @param type
// * @param context
// * @param msg
// */
//void debMsgOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);
///**
// * @brief registerSystemLogger  注册系统日志自定义事件
// */
//void BASELIBSHARED_EXPORT registerSystemLogger(const QString &logpath);
///**
// * @brief readLoggerConfig  读取logger.conf配置文件
// * @param dest
// * @param level
// * @param rFile
// * @param size
// */
//void readLoggerConfig(QString &dest, QString &level, QString &rFile, quint32 &size);
///**
// * @brief levelSprintf  等级是否输出校验
// * @param txt
// * @param type
// * @param level
// */
//void levelSprintf(QString &txt, const QtMsgType &type,const QString &level);
///**
// * @brief printf    日志输出
// * @param out
// * @param dest
// * @param rFile
// * @param type
// * @param size
// */
//void outputPrintf(const QString &out, const QString &dest, const QString &rFile, const QtMsgType &type, const quint32 size);
//}

#endif // LOGGER_H
