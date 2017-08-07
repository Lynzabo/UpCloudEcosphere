#include "terminalkeyutil.h"
#include "../dao/csterminaldao.h"
#include "db.h"
#include "avro.h"
using namespace Environment::Net_Equip_MainType;
using namespace Environment::EquipState;
using QtJson::JsonArray;
using QtJson::JsonObject;
TerminalKeYUtil* TerminalKeYUtil::m_instance = new TerminalKeYUtil;

TerminalKeYUtil::TerminalKeYUtil()
{
    m_terminalKeyMap.clear();
}

TerminalKeYUtil::~TerminalKeYUtil()
{
    m_terminalKeyMap.clear();
}

void TerminalKeYUtil::init()
{
    QList<CsTerminal> terminals  = CSTerminalDao::listTerminalByState(USABLE);
    if(terminals.size() > 0)
    {
        for(int i=0; i<terminals.size(); i++)
        {
            m_terminalKeyMap.insert(terminals.at(i).getTerminalUUID(), terminals.at(i));
        }
    }
}


bool TerminalKeYUtil::updateTerminalKey(const quint64 &uuid, const QString &newPubKey, const QString &newPriKey)
{
    mutex.lock();

    ////[1]将当前Map中的对应的终端转态改为不可用
    if(m_terminalKeyMap.contains(uuid) == true)
    {
        ((CsTerminal)(m_terminalKeyMap.value(uuid))).setState(DISABLED);
    }
    else
    {
        mutex.unlock();
        return false;
    }
    ////[2]修改数据库，更新密钥
    try{
        CSTerminalDao::updateTerminateKey(uuid, newPubKey, newPriKey);
    }
    catch(DBException& excep)
    {
        qDebug() << "DBError:" <<excep.getType() << excep.getText();
        mutex.unlock();
        return false;
    }
    ////[3]更改Map终端对应的终端的密钥和状态
    ((CsTerminal)(m_terminalKeyMap.value(uuid))).setPubKey(newPubKey);
    ((CsTerminal)(m_terminalKeyMap.value(uuid))).setPriKey(newPriKey);
    ((CsTerminal)(m_terminalKeyMap.value(uuid))).setState(USABLE);
    mutex.unlock();
    return true;
}

bool TerminalKeYUtil::getTerminalPubKey(const quint64 &uuid, QString &pubKey) const
{
    if(m_terminalKeyMap.contains(uuid) == true)
    {
        pubKey = m_terminalKeyMap.value(uuid).getPubKey();
        if(pubKey.isEmpty() == true)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}

bool TerminalKeYUtil::getTerminalPriKey(const quint64 &uuid, QString &priKey) const
{
    if(m_terminalKeyMap.contains(uuid) == true)
    {
        priKey = m_terminalKeyMap.value(uuid).getPriKey();
        if(priKey.isEmpty() == true)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}

void TerminalKeYUtil::terminalToJson(QString &msg, const CsTerminal terminal)
{
    JsonObject jsonObj;
    jsonObj["uuid"] = terminal.getUUID();
    jsonObj["terminalUuid"] = terminal.getTerminalUUID();
    jsonObj["description"] = terminal.getDescription();
    jsonObj["macaddr"] = terminal.getMacAddr();
    jsonObj["ip"] = terminal.getIP();
    jsonObj["publicKey"] = terminal.getPubKey();
    jsonObj["privateKey"] = terminal.getPriKey();
    jsonObj["state"] = terminal.getState();
    jsonObj["runState"] = terminal.getRunState();
    jsonObj["createTime"] = terminal.getCreateTime();
    jsonObj["onlineTime"] = terminal.getOnlineTime();
    jsonObj["offlineTime"] = terminal.getOfflineTime();
    msg = QtJson::serialize(jsonObj);
}

void TerminalKeYUtil::terminalToJson(QString &msg, const QList<CsTerminal> terminalList)
{
    JsonArray jsonArray;
    foreach(const CsTerminal terminal,terminalList) {
        QString params;
        terminalToJson(params,terminal);
        jsonArray << params;
    }
    msg = QtJson::serialize(jsonArray);
}

bool TerminalKeYUtil::terminalFromJson(CsTerminal &terminal, const QString &msg)
{
    bool ok = false;
    JsonObject jsonObj = QtJson::parse(msg,ok).toMap();
    if(ok) {
        terminal.setUUID(jsonObj.value("uuid").toString());
        terminal.setTerminalUUID((quint64)jsonObj.value("terminalUuid").toLongLong());
        terminal.setType((quint8)jsonObj.value("type").toInt());
        terminal.setDescription(jsonObj.value("description").toString());
        terminal.setMacAddr(jsonObj.value("macaddr").toString());
        terminal.setIP(jsonObj.value("ip").toString());
        terminal.setPubKey(jsonObj.value("publicKey").toString());
        terminal.setPriKey(jsonObj.value("privateKey").toString());
        terminal.setState((quint8)jsonObj.value("state").toInt());
        terminal.setRunState((quint8)jsonObj.value("runState").toInt());
        terminal.setCreateTime(jsonObj.value("createTime").toString());
        terminal.setOnlineTime(jsonObj.value("onlineTime").toString());
        terminal.setOfflineTime(jsonObj.value("offlineTime").toString());
    }
    return ok;
}

bool TerminalKeYUtil::terminalFromJson(QList<CsTerminal> &terminalList, const QString &msg)
{
    bool ok;
    JsonArray jsonArray = QtJson::parse(msg,ok).toList();
    foreach(const QVariant &json,jsonArray) {
        CsTerminal terminal;
        ok = terminalFromJson(terminal,json.toString());
        if(!ok) {
            break;
        }
        terminalList.append(terminal);
    }
    return ok;
}
