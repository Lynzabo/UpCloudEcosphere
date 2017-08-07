#ifndef STRUCTPARS_H
#define STRUCTPARS_H


#include "base.h"
#include "db.h"
#include "util/parse/bean/structparsemeta.h"
#include "util/parse/bean/structparsedata.h"
#include "util/parse/core/struct1fileparser.h"

//文件状态：未解析
#define F_STATE_UNPARSE 0
//文件状态：正在解析
#define F_STATE_PARSING 1
//文件状态：已解析
#define F_STATE_PARSED 2

//线程状态：空闲
#define T_STATE_IDLE 0
//线程状态：忙碌
#define T_STATE_BUSY 1

class StructParser : public QObject
{
    Q_OBJECT
public:
    StructParser(QObject *parent = 0);
    /**
     * @brief init 初始化解析数据化文件
     * @param fileList  要解析的数据化文件列表
     * @param fileOutAsync  要解析的文件之间是否存在依赖，如果存在依赖应给[false],不存在依赖则给[true],可以多线程解析
     * @param fileOutAsyncCount 同时解析文件线程数目
     * @param fileInAsync   一个解析文件内部各个部分之间是否存在依赖，如果存在依赖应给[false],不存在依赖则给[true],可以多线程解析
     * @param fileInAsyncCount 解析每个文件线程数目
     */
    void init(const QList<QString> &fileList,
              const bool fileOutAsync = false, const quint32 fileOutAsyncCount = 1,
              const bool fileInAsync = false, const quint32 fileInAsyncCount = 1);
    void parse(void);
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

private slots:
    void on_parseBegin();
    void on_parseEnd();
    void on_parseOneFileEnd(Struct1FileParser* sParseManager, const QString& fileName);
    void on_parseProcess(quint32 parsedCount);
    void on_parseError(Struct1FileParser* sParseManager, const QString& fileName, const QString &errMsg);
private:    
    bool m_fileOutAsync;
    quint32 m_fileOutAsyncCount;
    bool m_fileInAsync;
    quint32 m_fileInAsyncCount;

    //已经解析完成的文件数量
    quint32 m_haveParsedCount;
    //每个要解析的文件 和 它对应的状态是未解析还是已解析
    QMap<QString, quint8> m_fManagers;
    //每个单一文件解析器线程和它对应的状态是空闲还是忙碌
    QMap<Struct1FileParser*, quint8> m_sManagers;

    void getTask();
private slots:
    //解析出错
    void on_subParseError(const QString& fileName, const QString &errMsg);    
    //解析结束
    void on_subParseEnd(const QString& fileName);
};

#endif // STRUCTPARS_H
