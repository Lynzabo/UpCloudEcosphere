#ifndef TASKEXECPOOL_H
#define TASKEXECPOOL_H
#include <QtCore>
/*
 传入的JSON串
 QString taskInJson("{"
                 "\"program\" : \"/opt/Tomcat/bin/startup.sh\","
                 "\"arguments\" : ["
                 "\"p_1\","
                 "\"p_2\","
                 "\"p_3\","
                 "\"p_4\","
                 "\"p_5\","
                 "\"p_.\""
                 "]"
                 "}");
返回的执行结果JSON串
QString taskOutJson("{"
                 "\"state\" : \"true\","
                 "\"result\" : \"taskExecResult\""
                 "}");
 */
class TaskExecPool :public QObject
{
    Q_OBJECT
public:
    TaskExecPool();
    /**
     * @brief init 初始化任务
     * @param taskName  任务名称（为一个JSON字符串）格式如下
     *
     */
    virtual void init(const QString &taskName) = 0;
    /**
     * @brief taskExec  执行任务
     */
    virtual void taskExec(void) = 0;
signals:
    //执行开始
    void evt_execBegin(const QString &taskName);
    //执行结束
    void evt_execEnd(const QString &taskName, const QString &result);

public slots:
    virtual void on_execBegin(const QString &taskName) = 0;
    virtual void on_execEnd(const QString &taskName, const QString &result) = 0;
};

#endif // TASKEXECPOOL_H
