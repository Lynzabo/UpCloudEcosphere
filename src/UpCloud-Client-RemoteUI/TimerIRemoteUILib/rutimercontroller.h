#ifndef RUTIMERCONTROLLER_H
#define RUTIMERCONTROLLER_H
#include "timer.h"
#include "timeriremoteuilib_global.h"
#include "baseiremote.h"

class TIMERIREMOTEUILIBSHARED_EXPORT RUTimerController : public TimerController
{
public:
    RUTimerController();
    ~RUTimerController();
protected slots:
    /**
     * @brief start 开启计时器群组
     */
    virtual void on_start();
    /**
     * @brief start 停止计时器群组
     */
    virtual void on_stop();

protected:
    void timerEvent(QTimerEvent *event);
    /**
     * @brief on_write  读取Exector数据
     * @param context
     */
    virtual void on_write(PushContext *context);
private:
    ////定时扫描
    //心跳定时
    int timer_heartthrob;
    static QMutex *mutex;
    void asyncWork(Exector *ector);
};

#endif // RUTIMERCONTROLLER_H
