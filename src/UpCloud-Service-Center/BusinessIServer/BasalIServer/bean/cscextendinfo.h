#ifndef CSCLIENTEXTENDINFO_H
#define CSCLIENTEXTENDINFO_H
#include <QtCore>

class CsClientExtendInfo
{
public:
    CsClientExtendInfo();


    QString getUUID() const;
    void setUUID(const QString &value);

    quint64 getTerminalUUID() const;
    void setTerminalUUID(const quint64 &value);

    quint8 getType() const;
    void setType(const quint8 &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QString getIP() const;
    void setIP(const QString &value);

    QString getMacAddr() const;
    void setMacAddr(const QString &value);

    QString getPubKey() const;
    void setPubKey(const QString &value);

    QString getPriKey() const;
    void setPriKey(const QString &value);

    quint8 getState() const;
    void setState(const quint8 &value);

    quint8 getRunState() const;
    void setRunState(const quint8 &value);

    QString getCreateTime() const;
    void setCreateTime(const QString &value);

    QString getOnlineTime() const;
    void setOnlineTime(const QString &value);

    QString getOfflineTime() const;
    void setOfflineTime(const QString &value);

private:
    //UUID
    QString UUID;//
    //终端固定码
    quint64 terminalUUID;//
    //终端类型
    quint8 type;
    //描述
    QString description;
    //IP
    QString IP;
    //Mac地址
    QString macAddr;
    //公钥
    QString pubKey;
    //私钥
    QString priKey;
    //状态
    quint8 state;
    //运行状态
    quint8 runState;
    //创建时间
    QString createTime;//
    //上线时间
    QString onlineTime;
    //离线时间
    QString offlineTime;
};

#endif // CSCLIENTEXTENDINFO_H
