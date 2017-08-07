#ifndef ACTIONREQUESTFACTORY_H
#define ACTIONREQUESTFACTORY_H
#include "actionlib_global.h"
#include <QtCore>
/**
 * @brief The RegistryFactory class  请求动作动态注册中心
 */
class ACTIONLIBSHARED_EXPORT ActionRegistryFactory
{
public:
    template<typename T>
    static void registerClass(const quint8 &name)
    {
        


        QObject* obj = new T;
        constructors().insert(name, obj );
    }
    static QObject* createObject( const quint8& className, QObject* parent = NULL )
    {
        QObject* constructor = constructors().value(className);
        if ( constructor == NULL )
            return NULL;
        return (QObject*)constructor;
    }
private:
    static QHash<quint8, QObject*> instance;
    static QHash<quint8, QObject*>& constructors()
    {
        return instance;
    }
};

#endif // ACTIONREQUESTFACTORY_H
