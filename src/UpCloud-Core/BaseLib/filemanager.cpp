#include "filemanager.h"
#include <QDir>
#include "unicode.h"
QMutex* FileManager::lock = new QMutex;
FileManager::FileManager()
{

}

FileManager *FileManager::getInstance()
{
    static FileManager fileManager;
    return &fileManager;
}

void FileManager::writeLine(const QString &abst, const QString &fileName, const QString &txt, quint32 size)
{
    lock->lock();
    QDir *dir = new QDir(abst);
    if(!dir->exists())
    {
        dir->mkdir(abst);
        delete dir;
    }
    QDir::setCurrent(abst);
    QFileInfo logInfo(fileName);
    QString base = logInfo.baseName();
    QString ext = logInfo.completeSuffix();
    //如果文件大小大于10K就新建日志文件
    if(logInfo.size()>=(size*1024))
    {
        QDateTime currentDatetime = QDateTime::currentDateTime();
        QString newFileName = trs("%1_%2.%3").arg(base).arg(currentDatetime.toString("yyyy-MM-dd_HH-mm-ss")).arg(ext);
        QString newName = abst +newFileName;
        QString oldName = abst + fileName;
        QFile::rename(oldName,newName);


        QFile newFile(fileName);
        newFile.open(QIODevice::WriteOnly);
        newFile.close();
    }
    QFile outFile(fileName);
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;

    lock->unlock();
}

bool FileManager::loadTextFromFile(const QString &strFileName, QString &strText)
{
    QFile file(strFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream stream(&file);
    strText = stream.readAll();
    file.close();

    return true;
}

