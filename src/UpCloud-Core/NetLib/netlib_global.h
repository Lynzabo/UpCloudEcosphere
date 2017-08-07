#ifndef NETLIB_GLOBAL_H
#define NETLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(NETLIB_LIBRARY)
#  define NETLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define NETLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // NETLIB_GLOBAL_H
