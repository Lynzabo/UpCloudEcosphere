#include "nsabstpath.h"
SINGLETON_ALL_IN_ONE(NSAbstPath)
void NSAbstPath::setApplicationRootDir(const QString &rootDir)
{
    this->rootDir = rootDir;
}
