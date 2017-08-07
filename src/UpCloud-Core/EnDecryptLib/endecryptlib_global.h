#ifndef ENDECRYPTLIB_GLOBAL_H
#define ENDECRYPTLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ENDECRYPTLIB_LIBRARY)
#  define ENDECRYPTLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ENDECRYPTLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ENDECRYPTLIB_GLOBAL_H
