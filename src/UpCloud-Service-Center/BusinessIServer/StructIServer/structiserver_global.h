#ifndef STRUCTISERVER_GLOBAL_H
#define STRUCTISERVER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(STRUCTISERVER_LIBRARY)
#  define STRUCTISERVERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define STRUCTISERVERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // STRUCTISERVER_GLOBAL_H
