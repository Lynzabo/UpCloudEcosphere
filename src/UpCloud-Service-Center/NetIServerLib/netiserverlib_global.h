#ifndef NETISERVERLIB_GLOBAL_H
#define NETISERVERLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(NETISERVERLIB_LIBRARY)
#  define NETISERVERLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define NETISERVERLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // NETISERVERLIB_GLOBAL_H
