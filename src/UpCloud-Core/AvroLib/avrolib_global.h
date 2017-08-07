#ifndef AVROLIB_GLOBAL_H
#define AVROLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(AVROLIB_LIBRARY)
#  define AVROLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define AVROLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // AVROLIB_GLOBAL_H
