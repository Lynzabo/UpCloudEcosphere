/**************************************************************************
** Qt Creator license header template
**   Special keywords: Lynzabo 2016/1/24 2016
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/

#ifndef SOALIB_GLOBAL_H
#define SOALIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SOALIB_LIBRARY)
#  define SOALIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SOALIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SOALIB_GLOBAL_H
