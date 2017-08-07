#ifndef ERMLIB_GLOBAL_H
#define ERMLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ERMLIB_LIBRARY)
#  define ERMLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ERMLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ERMLIB_GLOBAL_H
