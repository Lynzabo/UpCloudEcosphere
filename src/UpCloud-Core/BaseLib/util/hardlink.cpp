#include "hardlink.h"


HardLink::HardLink()
{

}

int HardLink::creatFileHardLink(const QString &sourceFilePath, const QString &descFilePath)
{
    if(sourceFilePath.isEmpty())
    {
        qDebug() << "sourceFilePath is empty!";
        return -1;
    }
    if(descFilePath.isEmpty())
    {
        qDebug() << "descFilePath is empty!";
        return -1;
    }

    QFileInfo sourceFileInfo(sourceFilePath);
    if(sourceFileInfo.isFile() == false)
    {
        qDebug() << "sourceFilePath is not a file!";
        return -1;
    }
    if(sourceFileInfo.exists() == false)
    {
        qDebug() << "sourceFile is not exists!";
        return -1;
    }

    QFileInfo descFileInfo(descFilePath);
    if(descFileInfo.exists() == true)
    {
        qDebug() << "descFile is already exists!";
        return -1;
    }
    #ifdef Q_OS_WIN
    BOOL fCreatedLink = CreateHardLink((LPCWSTR)sourceFilePath.utf16(), (LPCWSTR)descFilePath.utf16(), NULL );
    if(fCreatedLink >=0 )
    {
        return 0;
    }
    else
    {
        return -1;
    }
    #else
        return link(sourceFilePath.toStdString().c_str(), descFilePath.toStdString().c_str());
    #endif
}

int HardLink::deleteFileHardLink(const QString &filePath)
{
    if(filePath.isEmpty())
    {
        qDebug() << "filePath is empty!";
        return -1;
    }

    QFileInfo fileInfo(filePath);
    if(fileInfo.isFile() == false)
    {
        qDebug() << "filePath is not a file!";
        return -1;
    }
    if(fileInfo.exists() == false)
    {
        qDebug() << "filePath is not exists!";
        return -1;
    }
 #ifdef Q_OS_WIN
    BOOL fDeleteLink = DeleteFile((LPCWSTR)filePath.utf16());
    if(fDeleteLink >=0 )
    {
        return 0;
    }
    else
    {
        return -1;
    }
#else
    return unlink(filePath.toStdString().c_str());
#endif
}

