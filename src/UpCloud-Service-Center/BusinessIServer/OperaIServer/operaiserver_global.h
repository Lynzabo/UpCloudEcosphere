#ifndef OPERAISERVER_GLOBAL_H
#define OPERAISERVER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(OPERAISERVER_LIBRARY)
#  define OPERAISERVERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define OPERAISERVERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // OPERAISERVER_GLOBAL_H
