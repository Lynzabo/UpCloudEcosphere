#ifndef NSTIMERCONTROLLER_H
#define NSTIMERCONTROLLER_H
#include "timer.h"
#include "baseiclient.h"
#include "timericlientlib_global.h"

class TIMERICLIENTLIBSHARED_EXPORT NSTimerController : public TimerController
{
    Q_OBJECT
public:
    NSTimerController();
    ~NSTimerController();
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
    //非结构化任务处理,需要回执报文回执
    int timer_unstruct_task;
    //结构化任务处理,需要回执报文回执
    int timer_struct_down_task;
    //结构化任务处理,需要回执报文回执
    int timer_struct_parse_task;
    //控制传输任务处理,需要回执报文回执
    int timer_schedule_down_task;
    //控制传输任务处理,需要回执报文回执
    int timer_schedule_exec_task;
    static QMutex *mutex;
    void asyncWork(Exector *ector);
};

#endif // NSTIMERCONTROLLER_H
