#include "csbridgedao.h"

CSBridgeDao::CSBridgeDao()
{

}

bool CSBridgeDao::terminateIsExist(quint64 terminateUUID)
{
    QString sql = "select UUID from CS_TERMINAL where TERMINAL_UUID =:terminateUUID";
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

void CSBridgeDao::updateTerminate(quint64 &terminateUUID,
                                  QString &IP, QString &MACAddr, QString &pubKey, QString &priKey,
                                  quint8 state, QString &onlineTime, QString &offlineTime)
{
    QString sql = "update CS_TERMINAL set"
                  "IP=:IP, MACADDR=:MACADDR, PUBLIC_KEY=:PUBLIC_KEY,PRIVATE_KEY=:PRIVATE_KEY,"
                  "STATE=:STATE, ONLINE_TIME=:ONLINE_TIME, OFFLINE_TIME=:OFFLINE_TIME "
                  "where TERMINAL_UUID=:TERMINAL_UUID";
    QVariantMap params;
    params["IP"] = IP;
    params["MACADDR"] = MACAddr;
    params["PUBLIC_KEY"] = pubKey;
    params["PRIVATE_KEY"] = priKey;
    params["STATE"] = state;
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

void CSBridgeDao::addTerminate(CsTerminal &terminate)
{
    QString sql = "insert into CS_TERMINAL values"
                  "(:UUID,:TERMINAL_UUID,:MACADDR,:IP,:TYPE,:PUBLIC_KEY,:PRIVATE_KEY,:STATE,:CREATE_TIME,:ONLINE_TIME,:OFFLINE_TIME)";
    QVariantMap params;
    params["UUID"] = terminate.getUUID();
    params["TERMINAL_UUID"] = terminate.getTerminalUUID();
    params["MACADDR"] = terminate.getMacAddr();
    params["IP"] = terminate.getIP();
    params["TYPE"] = terminate.getType();
    params["PUBLIC_KEY"] = terminate.getPubKey();
    params["PRIVATE_KEY"] = terminate.getPriKey();
    params["STATE"] = terminate.getState();
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

