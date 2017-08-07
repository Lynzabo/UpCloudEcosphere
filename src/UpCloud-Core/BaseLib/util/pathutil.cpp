#include "pathutil.h"
#include <QDir>
#include <QCoreApplication>

SINGLETON_ALL_IN_ONE(PathUtil)
QString PathUtil::absoluteFilePath(const QString &dir, const QString &fileName) const
{
    QDir *rootDir = new QDir(dir);
    const QString abstPath = rootDir->absoluteFilePath(QString("Makefile"));
    delete rootDir;
    return abstPath;
}

QString PathUtil::executeDir()
{
    QString strPath = QCoreApplication::applicationDirPath();
    backslash2Slash(strPath);
    return strPath;
}

QString PathUtil::executePath()
{
    return QCoreApplication::applicationFilePath();
}

QString PathUtil::executeName() const
{
    return QCoreApplication::applicationName();
}

void PathUtil::backslash2Slash(QString &strPath)
{
#ifdef Q_OS_WIN
    strPath.replace('\\', '/');
    if (strPath.endsWith('/'))
        return;
    strPath += '/';
#endif
}




