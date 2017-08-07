#ifndef COREPOJO_H
#define COREPOJO_H
#include <QtCore>
#include "ermlib_global.h"
/**
 * @brief The CorePOJO class    远程UI/中心数据交互核心实体共享
 */
class ERMLIBSHARED_EXPORT CorePOJO
{
public:
    CorePOJO();
    quint16 getState() const;
    void setState(const quint16 &value);

    QString getStateDesc() const;
    void setStateDesc(const QString &value);

    QString getContent() const;
    void setContent(const QString &value);

private:
    /**
     * @brief state 远程交互状态码
     */
    quint16 state;
    /**
     * @brief stateDesc 远程交互状态描述信息
     */
    QString stateDesc;
    /**
     * @brief content   远程交互传输数据内容
     */
    QString content;
};

#endif // COREPOJO_H
