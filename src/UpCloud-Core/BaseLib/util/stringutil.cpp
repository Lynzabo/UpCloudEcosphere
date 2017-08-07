#include "stringutil.h"


void StringUtil::formatSQLInParamsToInSQLCondition(const QStringList &strList, QString &inCondition)
{
    if(strList.size() <= 0)
        return;
    inCondition.clear();
    inCondition.append("'");
    inCondition.append(strList.join("','"));
    inCondition.append("'");
}

void StringUtil::formatSQLInParamsToInSQLCondition(QString &sql, QVariantMap & params,const QStringList &strList,const QString &indicate)
{
    if(strList.size() <= 0) {
        return;
    }
    QString inStr;inStr.clear();
    QString keyStr;
    int i =0;
    for(i = 0;i < strList.size();++i) {
        keyStr = indicate;
        params[keyStr.append(QString::number(i))] = strList.at(i);
        inStr.append(":");
        inStr.append(keyStr);
        if(i != strList.size() -1) {
            inStr.append(",");
        }
    }
    sql.replace(indicate,inStr);
}

SINGLETON_ALL_IN_ONE(StringUtil)
