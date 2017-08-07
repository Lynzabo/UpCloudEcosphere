#include "csabstpath.h"
SINGLETON_ALL_IN_ONE(CSAbstPath)

void CSAbstPath::setApplicationRootDir(const QString &rootDir)
{
    this->rootDir = rootDir;
}
