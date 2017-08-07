#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <QtCore>
#include "baselib_global.h"
class BASELIBSHARED_EXPORT FileManager
{
private:
    FileManager();
public:
    static FileManager *getInstance();
    ////用的时候补充
    /**
     * @brief writeLine 往文本文件追加字符串
     * @param abst  文件存放目录，目录必须以/结尾
     * @param fileName
     * @param txt
     * @param size
     */
    void writeLine(const QString &abst, const QString &fileName, const QString &txt, quint32 size);

    /**
     * @brief loadTextFromFile  读取文件数据
     * @param strFileName   文件名
     * @param strText   文件内容
     * @return  返回读取状态
     */
    bool loadTextFromFile(const QString& strFileName, QString& strText);
    //FileManager::getInstance()->writeLine(QString("d:/111/"),QString("111.txt"),QString("aaaa"));
private:
   static QMutex* lock;
};

#endif // FILEMANAGER_H
