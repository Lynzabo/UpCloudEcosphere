#ifndef STRUCTPARSEDATATHREAD_H
#define STRUCTPARSEDATATHREAD_H
#include <QtCore>

#include "base.h"
#include "db.h"
#include "bean/structparsedata.h"

class StructParseDataThread : public QThread
{
    Q_OBJECT
public:
    StructParseDataThread(QString xmlFilePath, quint32 refBegin, quint32 refEnd, DBTransaction &dbTransaction)
        : m_xmlFilePath(xmlFilePath), m_refBegin(refBegin), m_refEnd(refEnd),m_dbTransaction(dbTransaction){}

signals:
    void evt_parseError(const QString &errMsg);
    void evt_dbExecError(const StructParseData& data, const DBException &dbException);

    void evt_subParseDataBegin();
    void evt_subPareDataEnd();

    void evt_subPareDataItem();

protected:
    void run();

private:
    QString m_xmlFilePath;
    quint32 m_refBegin;
    quint32 m_refEnd;
    DBTransaction m_dbTransaction;

    StructParseData m_currentData;


    bool parseDataItem();
};

#endif // STRUCTPARSEDATATHREAD_H
