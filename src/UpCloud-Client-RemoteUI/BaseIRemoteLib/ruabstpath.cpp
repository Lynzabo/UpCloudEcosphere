#include "ruabstpath.h"
SINGLETON_ALL_IN_ONE(RUAbstPath)

void RUAbstPath::setApplicationRootDir(const QString &rootDir)
{
    this->rootDir = rootDir;
}
