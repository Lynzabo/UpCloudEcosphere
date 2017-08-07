#ifndef STRUCTPARSEMANAGER_H
#define STRUCTPARSEMANAGER_H

#include "base.h"
#include "db.h"
#include "structiclient_global.h"
#include "bean/structparsemeta.h"
#include "bean/structparsedata.h"
#include "structparsedatathread.h"



class STRUCTICLIENTSHARED_EXPORT StructParseManager : public QThread
{
    Q_OBJECT
public:
    /**
     * @brief StructParseManager 解析XML文件管理器
     * @param xmlFilePath        XML文件路径
     * @param async              是否支持多路解析，支持为true，不支持为false
     * @param asyncNum           如果支持多路解析,通道数量
     */
    StructParseManager(QString xmlFilePath, bool async, quint32 asyncNum);

    ~StructParseManager();

public slots:
    void parse(void);
protected:
    void run();
signals:
    //解析出错---解析数据文件本身出错
    void evt_parseError(const QString &errMsg);
    //解析出错---执行解析数据，操作数据库出错
    void evt_dbConnError(const DBException &dbException);
    void evt_dbExecError(const StructParseData& data, const DBException &dbException);

    //解析开始
    void evt_parseBegin();
    //解析结束
    void evt_parseEnd();
    //解析进度
    void evt_parseProcess(quint32 parsedCount);

private slots:
    void on_parseError(const QString &errMsg);
    void on_dbExecError(const StructParseData& data, const DBException &dbException);

    void on_subPareDataEnd();
    void on_subPareDataItem();

private:
    QString m_xmlFilePath;
    bool m_async;
    quint32 m_asyncNum;
    quint32 m_size;    
    quint32 m_parsedCount;

    StructParseMeta::Builder* m_parseBuilder;
    StructParseMeta* m_structParseMeta;

    DatabaseMeta::Builder *m_dbBuilder;
    DatabaseMeta *m_dbMeta;
    DBTransaction *m_dbTransaction;

    QMap<StructParseDataThread*, bool> m_parseDataThreads;
    QMap<quint32, quint32> m_begEnds;

    bool parseMeta(void);
    bool dbConnect();
    void group();
    void parseData(void);

    void doError();
};

#endif // STRUCTPARSEMANAGER_H
