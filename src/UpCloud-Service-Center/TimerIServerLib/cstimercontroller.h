#ifndef CSTIMERCONTROLLER_H
#define CSTIMERCONTROLLER_H
#include "timer.h"
#include "baseiserver.h"
#include "timeriserverlib_global.h"
/**
 * @brief The CSTimerController class   中心服务器端计数控制
 */

class TIMERISERVERLIBSHARED_EXPORT CSTimerController : public TimerController
{
    Q_OBJECT
public:
    CSTimerController();
    ~CSTimerController();
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
    //非结构化任务
    int timer_unstruct_task;
    //结构化任务
    int timer_struct_task;
    //控制传输任务
    int timer_schedule_task;
    static QMutex *mutex;
    void asyncWork(Exector *ector);
};

#endif // CSTIMERCONTROLLER_H
