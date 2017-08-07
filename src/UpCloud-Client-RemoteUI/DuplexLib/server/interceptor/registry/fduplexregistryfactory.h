#ifndef FDUPLEXREGISTRYFACTORY_H
#define FDUPLEXREGISTRYFACTORY_H
#include "duplexlib_global.h"
#include <QtCore>
/**
 * @brief The FDuplexRegistryFactory class  远程UI操作服务提供注册中心
 */
class DUPLEXLIBSHARED_EXPORT FDuplexRegistryFactory
{
public:
    template<typename T>
    static void registerClass(const quint16 &name)
    {
        constructors().insert( name, &constructorHelper<T> );
    }
    static QObject* createObject( const quint16& className, QObject* parent = NULL )
    {
        Constructor constructor = constructors().value( className );
        if ( constructor == NULL )
            return NULL;
        return (*constructor)();
    }
    static bool contains(const quint16 className)
    {
         return constructors().keys().contains(className);
    }
private:
    typedef QObject* (*Constructor)();
    template<typename T>
    static QObject* constructorHelper()
    {
        return new T;
    }
    static QHash<quint16, Constructor>& constructors()
    {
        static QHash<quint16, Constructor> instance;
        return instance;
    }
};

#endif // FDUPLEXREGISTRYFACTORY_H
