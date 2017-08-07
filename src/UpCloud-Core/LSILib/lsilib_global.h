/**************************************************************************
**   UpCloudEcosphere
**   Copyright (c) UpCloud C/C++ development team.
**   All rights 2016 reserved.
**   Author : dyk
**************************************************************************/

#ifndef LSILIB_GLOBAL_H
#define LSILIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LSILIB_LIBRARY)
#  define LSILIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LSILIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LSILIB_GLOBAL_H
