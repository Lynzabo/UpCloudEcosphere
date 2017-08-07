#ifndef RESPONSEFACTORY_H
#define RESPONSEFACTORY_H
#include "actionlib_global.h"
#include "response/abstractresponse.h"
#include <QtCore>

/**
 * @brief The RequestFactory class  响应动作动态注册中心
 */
class ACTIONLIBSHARED_EXPORT ResponseFactory
{
public:
    template<typename T>
    static void registerClass(const QString &name)
    {
        constructors().insert( name, &constructorHelper<T> );
    }
    static QObject* createObject( const QString& className, QObject* parent = NULL )
    {
        Constructor constructor = constructors().value( className );
        if ( constructor == NULL )
            return NULL;
        return (*constructor)( parent );
    }
private:
    typedef QObject* (*Constructor)( QObject* parent );
    template<typename T>
    static QObject* constructorHelper( QObject* parent )
    {
        AbstractResponse *pa = qobject_cast<AbstractResponse*>(parent);
        return new T( pa );
    }
    static QHash<QString, Constructor>& constructors()
    {
        static QHash<QString, Constructor> instance;
        return instance;
    }
};
#endif // RESPONSEFACTORY_H
