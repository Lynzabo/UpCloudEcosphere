#ifndef CSCLIENTGROUPASSOC_H
#define CSCLIENTGROUPASSOC_H
#include <QtCore>

class CsClientGroupAssoc
{

public:
    CsClientGroupAssoc();

    QString getUuid() const;
    void setUuid(const QString &value);

    QString getClientUuid() const;
    void setClientUuid(const QString &value);

    QString getGroupUuid() const;
    void setGroupUuid(const QString &value);

    QString getInsertor() const;
    void setInsertor(const QString &value);

    QString getInsertTime() const;
    void setInsertTime(const QString &value);

    qint32 getSequence() const;
    void setSequence(const qint32 &value);

    quint16 getState() const;
    void setState(const quint16 &value);

private:
    //UUID
    QString uuid;
    //客户端UUID
    QString clientUuid;
    //节点服务器组UUID
    QString groupUuid;
    //添加人
    QString insertor;
    //添加时间
    QString insertTime;
    //排序
    qint32 sequence;
    //状态
    quint16 state;
};

#endif // CSCLIENTGROUPASSOC_H
