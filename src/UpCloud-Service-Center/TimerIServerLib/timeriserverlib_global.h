#ifndef TIMERISERVERLIB_GLOBAL_H
#define TIMERISERVERLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TIMERISERVERLIB_LIBRARY)
#  define TIMERISERVERLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TIMERISERVERLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // TIMERISERVERLIB_GLOBAL_H
