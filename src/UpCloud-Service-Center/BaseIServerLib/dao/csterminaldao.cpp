#include "csterminaldao.h"
#include "db.h"
CSTerminalDao::CSTerminalDao()
{

}

QList<CsTerminal> CSTerminalDao::listTerminalByClientUUid(const QString &clientUUid)
{

    QString sql = "select * from CS_CLIENT_TERMINAL where CLIENT_UUID LIKE (:clientUuid)";
    DBQuery query;
    QVariantMap params;
    params["clientUUid"] = clientUUid;
    return query.listBeans(mapToCsTerminal,sql,params);
}

QList<CsTerminal> CSTerminalDao::listTerminalByState(const quint8 state)
{
    QString tasksql = "select * from CS_CLIENT_TERMINAL where STATE=:state";

    QVariantMap params;
    params["state"] = state;
    DBQuery dbquery;
    return dbquery.listBeans(mapToCsTerminal,tasksql,params);
}

QList<CsTerminal> CSTerminalDao::listTerminalByStateAndType(const quint8 state, const qint8 type)
{
    QString tasksql = "select * from CS_CLIENT_TERMINAL where STATE=:state and TYPE=:type";

    QVariantMap params;
    params["state"] = state;
    params["type"] = type;
    DBQuery dbquery;
    return dbquery.listBeans(mapToCsTerminal,tasksql,params);
}

QList<CsTerminal> CSTerminalDao::listTerminalByRunState(const quint8 state)
{
    QString tasksql = "select * from CS_CLIENT_TERMINAL where RUNSTATE=:state";

    QVariantMap params;
    params["state"] = state;
    DBQuery dbquery;
    return dbquery.listBeans(mapToCsTerminal,tasksql,params);
}

bool CSTerminalDao::terminateIsExist(const quint64& terminateUUID)
{
    QString sql = "select UUID from CS_CLIENT_TERMINAL where TERMINAL_UUID =:terminateUUID";
    QVariantMap params;
    params["terminateUUID"] = terminateUUID;
    DBQuery query;
    QVariantMap result;result.clear();
    result = query.uniqueResult(sql,params);
    if(result.size()>0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CSTerminalDao::updateTerminate(const quint64 &terminateUUID,
                                    const QString &IP, const QString &MACAddr,
                                    const QString &pubKey, const QString &priKey,
                                    const quint8 runState, const QString &onlineTime, const QString &offlineTime)
{
    QString sql = "update CS_CLIENT_TERMINAL set "
                  "IP=:IP, MACADDR=:MACADDR, PUBLIC_KEY=:PUBLIC_KEY, PRIVATE_KEY=:PRIVATE_KEY,"
                  "RUNSTATE=:RUNSTATE, ONLINE_TIME=:ONLINE_TIME, OFFLINE_TIME=:OFFLINE_TIME "
                  "where TERMINAL_UUID=:TERMINAL_UUID";
    QVariantMap params;
    params["IP"] = IP;
    params["MACADDR"] = MACAddr;
    params["PUBLIC_KEY"] = pubKey;
    params["PRIVATE_KEY"] = priKey;
    params["RUNSTATE"] = runState;
    params["ONLINE_TIME"] = onlineTime;
    params["OFFLINE_TIME"] = offlineTime;
    params["TERMINAL_UUID"] = terminateUUID;

    DBTransaction *transaction = new DBTransaction;
    transaction->beginTransaction();
    bool ok;
    ok = transaction->execSQL(sql,params);
    if(!ok) {
        goto end;
    }

    transaction->commit();
    delete transaction;
    return;
end:;
    transaction->rollback();
    delete transaction;
    DBException excep;
    excep.setText(trs("更新固定码为%1的客户端失败").arg(QString::number(terminateUUID)));
    excep.setType(QSqlError::TransactionError);
    throw excep;
}

void CSTerminalDao::updateTerminateKey(const quint64 &terminateUUID, const QString &pubKey, const QString &priKey)
{
    QString sql = "update CS_CLIENT_TERMINAL set "
                  "PUBLIC_KEY=:PUBLIC_KEY, PRIVATE_KEY=:PRIVATE_KEY "
                  "where TERMINAL_UUID=:TERMINAL_UUID";
    QVariantMap params;
    params["PUBLIC_KEY"] = pubKey;
    params["PRIVATE_KEY"] = priKey;
    params["TERMINAL_UUID"] = terminateUUID;

    DBTransaction *transaction = new DBTransaction;
    transaction->beginTransaction();
    bool ok;
    ok = transaction->execSQL(sql,params);
    if(!ok) {
        goto end;
    }

    transaction->commit();
    delete transaction;
    return;
end:;
    transaction->rollback();
    delete transaction;
    DBException excep;
    excep.setText(trs("更新固定码为%1的密钥失败 ").arg(QString::number(terminateUUID)));
    excep.setType(QSqlError::TransactionError);
    throw excep;
}

void CSTerminalDao::addTerminate(const CsTerminal &terminate)
{
    QString sql = "insert into CS_CLIENT_TERMINAL values"
                  "(:UUID,:TERMINAL_UUID,:TYPE,:DESCRIPTION,:MACADDR,:IP,:PUBLIC_KEY,:PRIVATE_KEY,:STATE,:RUNSTATE,:CREATE_TIME,:ONLINE_TIME,:OFFLINE_TIME)";
    QVariantMap params;
    params["UUID"] = terminate.getUUID();
    params["TERMINAL_UUID"] = terminate.getTerminalUUID();
    params["TYPE"] = terminate.getType();
    params["DESCRIPTION"] = terminate.getDescription();
    params["MACADDR"] = terminate.getMacAddr();
    params["IP"] = terminate.getIP();
    params["PUBLIC_KEY"] = terminate.getPubKey();
    params["PRIVATE_KEY"] = terminate.getPriKey();
    params["STATE"] = terminate.getState();
    params["RUNSTATE"] = terminate.getRunState();
    params["CREATE_TIME"] = terminate.getCreateTime();
    params["ONLINE_TIME"] = terminate.getOnlineTime();
    params["OFFLINE_TIME"] = terminate.getOfflineTime();

    DBTransaction *transaction = new DBTransaction;
    transaction->beginTransaction();
    bool ok;
    ok = transaction->execSQL(sql,params);
    if(!ok) {
        goto end;
    }

    transaction->commit();
    delete transaction;
    return;
end:;
    transaction->rollback();
    delete transaction;
    DBException excep;
    excep.setText(trs("添加固定码为%1的客户端失败").arg(terminate.getTerminalUUID()));
    excep.setType(QSqlError::TransactionError);
    throw excep;
}

CsTerminal CSTerminalDao::mapToCsTerminal(const QVariantMap &rowMap)
{
    CsTerminal terminal;
    terminal.setUUID(rowMap.value("UUID").toString());
    terminal.setTerminalUUID(rowMap.value("TERMINAL_UUID").toLongLong());
    terminal.setType((quint8)rowMap.value("TYPE").toUInt());
    terminal.setDescription(rowMap.value("DESCRIPTION").toString());
    terminal.setMacAddr(rowMap.value("MACADDR").toString());
    terminal.setIP(rowMap.value("IP").toString());
    terminal.setPubKey(rowMap.value("PUBLIC_KEY").toString());
    terminal.setPriKey(rowMap.value("PRIVATE_KEY").toString());
    terminal.setState((quint8)rowMap.value("STATE").toUInt());
    terminal.setRunState((quint8)rowMap.value("RUNSTATE").toUInt());
    terminal.setCreateTime(rowMap.value("CREATE_TIME").toString());
    terminal.setOnlineTime(rowMap.value("ONLINE_TIME").toString());
    terminal.setOfflineTime(rowMap.value("OFFLINE_TIME").toString());
    return terminal;
}

