#include "taskoutjson.h"

TaskOutJson::TaskOutJson()
{
    this->clear();
}

void TaskOutJson::clear()
{
    m_state = false;
    m_result.clear();
}
bool TaskOutJson::state() const
{
    return m_state;
}

void TaskOutJson::setState(bool state)
{
    m_state = state;
}
QString TaskOutJson::result() const
{
    return m_result;
}

void TaskOutJson::setResult(const QString &result)
{
    m_result = result;
}



