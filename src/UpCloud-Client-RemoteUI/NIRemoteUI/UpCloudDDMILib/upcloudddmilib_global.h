#ifndef UPCLOUDDDMILIB_GLOBAL_H
#define UPCLOUDDDMILIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(UPCLOUDDDMILIB_LIBRARY)
#  define UPCLOUDDDMILIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define UPCLOUDDDMILIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // UPCLOUDDDMILIB_GLOBAL_H
