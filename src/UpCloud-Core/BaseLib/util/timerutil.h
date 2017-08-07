#ifndef TIMERUTIL_H
#define TIMERUTIL_H
#include <QtCore>
#include <sys/timeb.h>
#include <time.h>
#include "baselib_global.h"
#include "unicode.h"
/**
 *  定义时间操作工具类
 */
class BASELIBSHARED_EXPORT TimerUtil
{
public:
    TimerUtil();
public:
    /**
     * @brief toString  获取当前时间
     * @param format
     */
    static void toString(QString &curTime, const QString &format = QString("yyyy-MM-dd HH:mm:ss"));
    /**
     * @brief currentTimeMillis 返回quint64类型当前时间
     * @return
     * 使用方法:
     *  quint64 tim = TimerUtil::currentTimeMillis();
     */
    static quint64 currentTimeMillis();
    /**
     * @brief currentTime   转换quint64类型时间为字符串类型时间
     * @param t
     * @return
     * 格式为:2015-12-12 12:12:12
     * 使用方法:
     *  quint64 tim = TimerUtil::currentTimeMillis();
     *  QString time;
     *  TimerUtil::quint64ToQString(tim,time);
     *  qDebug() << tim << ":" << time;
     */
    static void quint64ToQString(const quint64 &t, QString &ti);
    /**
     * @brief format    格式化日期+时间字符串
     * @param srcTime   源日期+时间字符串
     * @param descTime  目标日期+时间字符串
     * @param format    格式
     * throw QString
     */
    static void format(const QString &srcTime,QString &descTime,const QString& format = trs("yyyy-MM-dd HH:mm:ss"));
    /**
     * @brief toCanDisplayTime  转换时间为可给用户展示的时间,如与当前时间间隔60s之内,返回刚刚,与当前时间间隔1天,返回1天前
     * @param time
     * @param format
     * @return
     */
    QString toCanDisplayTime(const QString &time, const QString &format = QString("yyyy-MM-dd HH:mm:ss"));
};

#endif // TIMERUTIL_H
