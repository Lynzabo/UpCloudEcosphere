#ifndef TASKINJSON_H
#define TASKINJSON_H

#include <QtCore>

class TaskInJson
{
public:
    TaskInJson();

    void clear();

    QString program() const;
    void setProgram(const QString &program);

    QStringList arguments() const;
    void setArguments(const QStringList &arguments);

private:
    //执行程序名
    QString m_program;
    //执行程序参数列表
    QStringList m_arguments;

};

#endif // TASKINJSON_H
