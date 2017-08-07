#ifndef TASKOUTJSON_H
#define TASKOUTJSON_H

#include <QtCore>

class TaskOutJson
{
public:
    TaskOutJson();

    void clear();

    bool state() const;
    void setState(bool state);

    QString result() const;
    void setResult(const QString &result);

private:
    //执行状态【成功】/【失败】
    bool m_state;
    //执行结果 如果是失败，则为程序失败信息，如果是成功，则为程序正常运行结果
    QString m_result;
};

#endif // TASKOUTJSON_H
