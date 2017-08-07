#ifndef MQLIB_GLOBAL_H
#define MQLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MQLIB_LIBRARY)
#  define MQLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MQLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MQLIB_GLOBAL_H
