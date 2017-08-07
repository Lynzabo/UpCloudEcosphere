#ifndef BASELIB_GLOBAL_H
#define BASELIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BASELIB_LIBRARY)
#  define BASELIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define BASELIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // BASELIB_GLOBAL_H
