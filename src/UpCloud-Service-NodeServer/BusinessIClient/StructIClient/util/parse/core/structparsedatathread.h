#ifndef STRUCTPARSEDATATHREAD_H
#define STRUCTPARSEDATATHREAD_H
#include <QtCore>

#include "base.h"
#include "db.h"
#include "util/parse/bean/structparsedata.h"

class StructParseDataThread : public QThread
{
    Q_OBJECT
public:
    StructParseDataThread(QString xmlFilePath, quint32 refBegin, quint32 refEnd, DBTransaction* dbTransaction)
        : m_xmlFilePath(xmlFilePath), m_refBegin(refBegin), m_refEnd(refEnd),m_dbTransaction(dbTransaction){}
    ~StructParseDataThread();
signals:
    void evt_parseError(const QString &errMsg);    

    void evt_subParseDataBegin();
    //parse block end
    void evt_subPareDataEnd();
    //parse block one item end
    void evt_subPareDataItem();

protected:
    void run();

private:
    QString m_xmlFilePath;
    quint32 m_refBegin;
    quint32 m_refEnd;
    DBTransaction* m_dbTransaction;

    StructParseData m_currentData;

    //执行每一条SQL语句
    bool parseDataItem();
};

#endif // STRUCTPARSEDATATHREAD_H
