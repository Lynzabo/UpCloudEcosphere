#ifndef PARSESDPOOL_H
#define PARSESDPOOL_H
#include <QtCore>

class ParseSDPool:public QObject
{
    Q_OBJECT    
public:    
    /**
     * @brief parse 解析数据化文件
     * @param fileList  要解析的数据化文件列表
     * @param fileOutAsync  要解析的文件之间是否存在依赖，如果存在依赖应给[false],不存在依赖则给[true],可以多线程解析
     * @param fileOutAsyncCount 同时解析文件线程数目
     * @param fileInAsync   一个解析文件内部各个部分之间是否存在依赖，如果存在依赖应给[false],不存在依赖则给[true],可以多线程解析
     * @param fileInAsyncCount 解析每个文件线程数目
     */
    virtual void parse(const QList<QString> &fileList,
                       const bool fileOutAsync = false, const quint32 fileOutAsyncCount = 1,
                       const bool fileInAsync = false, const quint32 fileInAsyncCount = 1) = 0;
signals:   
    //解析开始
    void evt_parseBegin();
    //解析结束
    void evt_parseEnd();
    //解析一个文件结束
    void evt_parseOneFileEnd(const QString& fileName);
    //解析进度
    void evt_parseProcess(quint32 parsedCount);
    //解析出错
    void evt_parseError(const QString& fileName, const QString &errMsg);

public slots:
    virtual void on_parseBegin() = 0;
    virtual void on_parseEnd() = 0;
    virtual void on_parseOneFileEnd(const QString& fileName) = 0;
    virtual void on_parseProcess(quint32 parsedCount) = 0;
    virtual void on_parseError(const QString& fileName, const QString &errMsg) = 0;
};

#endif // PARSESDPOOL_H
