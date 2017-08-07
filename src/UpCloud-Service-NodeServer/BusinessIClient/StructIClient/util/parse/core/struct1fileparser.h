#ifndef STRUCT1FILEPAR_H
#define STRUCT1FILEPAR_H
#include "base.h"
#include "db.h"
#include "../bean/structparsedata.h"
#include "../bean/structparsemeta.h"
#include "structparsedatathread.h"

class Struct1FileParser : public QThread
{
    Q_OBJECT
public:

    Struct1FileParser();
    ~Struct1FileParser();

    /**
         * @brief init               解析单个XML文件管理器
         * @param fileName           XML文件名
         * @param async              是否支持多路解析，支持为true，不支持为false
         * @param asyncNum           如果支持多路解析,通道数量
         */
    void init(const QString &fileName, bool async = false, quint32 asyncNum = 0);

protected:
    void run();
signals:
    //解析出错
    void evt_parseError(const QString& fileName, const QString &errMsg);
    //解析开始
    void evt_parseBegin();
    //解析结束
    void evt_parseEnd(const QString& fileName);
    //解析进度
    void evt_parseProcess(quint32 parsedCount);

private slots:
    void on_parseError(const QString &errMsg);

    void on_subPareDataEnd();
    void on_subPareDataItem();

private:
    QString m_fileName;
    bool m_async;
    quint32 m_asyncNum;

    //解析失败信息列表
    QList<QString> m_errors;

    //解析文件中解析条目的数量
    quint32 m_size;
    //已经解析完成的条目数量
    quint32 m_parsedCount;

    //解析文件中的元数据
    StructParseMeta::Builder* m_parseBuilder;
    StructParseMeta* m_structParseMeta;

    //数据库连接元数据
    DatabaseMeta::Builder *m_dbBuilder;
    DatabaseMeta *m_dbMeta;

    //每个解析线程及对应的解析状态 [true]代表此线程解析完成 [false]代表解析未完成
    QMap<StructParseDataThread*, bool> m_parseDataThreads;
    //每个解析线程解析的起始位置 和  结束位置
    QMap<quint32, quint32> m_begEnds;
    DBTransaction* m_dbTransaction;
private:
    //解析文件元数据
    bool parseMeta(void);
    ////生成数据库元数据
    void getDbMeta();
    //分配线程组
    void group();
    //解析文件数据条目
    void parseData(void);
    //数据库连接
    bool dbConnect();
    //执行错误处理
    void doError();
};

#endif // STRUCT1FILEPAR_H
