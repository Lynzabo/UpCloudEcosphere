#ifndef SCHEDULEISERVER_GLOBAL_H
#define SCHEDULEISERVER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SCHEDULEISERVER_LIBRARY)
#  define SCHEDULEISERVERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SCHEDULEISERVERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SCHEDULEISERVER_GLOBAL_H