#include "timerutil.h"

TimerUtil::TimerUtil()
{

}

void TimerUtil::toString(QString &curTime , const QString &format)
{
    curTime = QDateTime::currentDateTime().toString(format);
}

quint64 TimerUtil::currentTimeMillis()
{
    timeb t;
    ftime(&t);
    return 1000 * t.time + t.millitm;
}

void TimerUtil::quint64ToQString(const quint64 &t, QString &ti)
{
    char tmpbuf[21];
    time_t timer = t;
    struct tm *tblock;
    timer = time(NULL);
    tblock = localtime(&timer);
    strftime(tmpbuf, 21, "%Y-%m-%d %H:%M:%S", tblock);
    ti = QString("%1").arg(tmpbuf);
}

void TimerUtil::format(const QString &srcTime, QString &descTime, const QString &format)
{
    if(srcTime.isEmpty())
    {
        throw trs("%1 is null").arg(srcTime);
    }
    else
    {
        descTime.clear();
        QDateTime dt = QDateTime::fromString(srcTime,format);
        if(dt.isValid())
        {
            descTime = dt.toString(format);
        }
        else
        {
            throw trs("%1 format error").arg(srcTime);
        }
    }
}

QString TimerUtil::toCanDisplayTime(const QString &time, const QString &format)
{
    QDateTime dt = QDateTime::fromString(time,format);
    QDateTime t(QDateTime::currentDateTime());
    int nElapseSecs = dt.secsTo(t);
    int nElapseDays = dt.daysTo(t);

    if (nElapseDays == 1) {
        return trs("昨天");
    } else if (nElapseDays == 2) {
        return trs("前天");
    } else if (nElapseDays > 2) {
        return dt.toString("yy-M-d");
    }

    if (nElapseSecs < 60) {
        // less than 1 minutes: "just now"
        return trs("刚刚");

    } else if (nElapseSecs >= 60 && nElapseSecs < 60 * 2) {
        // 1 minute: "1 minute ago"
        return trs("1分钟以前");

    } else if (nElapseSecs >= 120 && nElapseSecs < 60 * 60) {
        // 2-60 minutes: "x minutes ago"
        QString str = trs("%1分钟以前");
        return str.arg(nElapseSecs/60);

    } else if (nElapseSecs >= 60 * 60 && nElapseSecs < 60 * 60 * 2) {
        // 1 hour: "1 hour ago"
        return trs("1小时以前");

    } else if (nElapseSecs >= 60 * 60 * 2 && nElapseSecs < 60 * 60 * 24) {
        // 2-24 hours: "x hours ago"
        QString str = trs("%1小时以前");
        return str.arg(nElapseSecs/60/60);
    }

    return QString("Error");
}

