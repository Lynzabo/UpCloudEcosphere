#ifndef SCHEDULEICLIENT_GLOBAL_H
#define SCHEDULEICLIENT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SCHEDULEICLIENT_LIBRARY)
#  define SCHEDULEICLIENTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SCHEDULEICLIENTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SCHEDULEICLIENT_GLOBAL_H
