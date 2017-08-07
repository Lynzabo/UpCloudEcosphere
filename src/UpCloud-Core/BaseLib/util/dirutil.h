#ifndef DIRUTIL_H
#define DIRUTIL_H

#include <QtCore>
#include "baselib_global.h"
class BASELIBSHARED_EXPORT DirUtil
{
public:   
   static  bool DeleteDirectory(const QString &dirPath);
};

#endif // DIRUTIL_H
