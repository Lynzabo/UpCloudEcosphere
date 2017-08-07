#ifndef PARSESDPOOLIMPL_H
#define PARSESDPOOLIMPL_H

#include "parsesdpool.h"
#include "util/parse/structparser.h"

class ParseSDPoolImpl : public ParseSDPool
{
    Q_OBJECT
public:
    ParseSDPoolImpl();
    ~ParseSDPoolImpl();

public:
    /**
     * @brief parse 解析数据化文件
     * @param fileList  要解析的数据化文件列表
     * @param fileOutAsync  要解析的文件之间是否存在依赖，如果存在依赖应给[false],不存在依赖则给[true],可以多线程解析
     * @param fileOutAsyncCount 同时解析文件线程数目
     * @param fileInAsync   一个解析文件内部各个部分之间是否存在依赖，如果存在依赖应给[false],不存在依赖则给[true],可以多线程解析
     * @param fileInAsyncCount 解析每个文件线程数目
     */
    void parse(const QList<QString> &fileList,
                       const bool fileOutAsync = false, const quint32 fileOutAsyncCount = 1,
                       const bool fileInAsync = false, const quint32 fileInAsyncCount = 1);

protected slots:
    void on_parseBegin();
    void on_parseEnd();
    void on_parseOneFileEnd(const QString& fileName);
    void on_parseProcess(quint32 parsedCount);
    void on_parseError(const QString& fileName, const QString &errMsg);
private:
    StructParser* m_parseManager;
};

#endif // PARSESDPOOLIMPL_H
