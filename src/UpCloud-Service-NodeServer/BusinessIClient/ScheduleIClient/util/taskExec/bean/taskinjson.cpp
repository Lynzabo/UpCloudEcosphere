#include "taskinjson.h"

TaskInJson::TaskInJson()
{
    this->clear();
}

void TaskInJson::clear()
{
    m_program.clear();
    m_arguments.clear();
}
QString TaskInJson::program() const
{
    return m_program;
}

void TaskInJson::setProgram(const QString &program)
{
    m_program = program;
}

QStringList TaskInJson::arguments() const
{
    return m_arguments;
}

void TaskInJson::setArguments(const QStringList &arguments)
{
    m_arguments = arguments;
}



