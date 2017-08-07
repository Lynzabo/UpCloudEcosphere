#include "dirutil.h"

bool DirUtil::DeleteDirectory(const QString &dirPath)
{
    if (dirPath.isEmpty())
            return false;

        QDir dir(dirPath);
        if(!dir.exists())
            return true;

        dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
        QFileInfoList fileList = dir.entryInfoList();
        foreach (QFileInfo fi, fileList)
        {
            if (fi.isFile())
                fi.dir().remove(fi.fileName());
            else
                DeleteDirectory(fi.absoluteFilePath());
        }
        return dir.rmpath(dir.absolutePath());
}
