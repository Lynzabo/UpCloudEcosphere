#ifndef CSCLIENTGROUP_H
#define CSCLIENTGROUP_H
#include <QtCore>

class CsClientGroup
{
public:
    CsClientGroup();
    QString getUuid() const;
    void setUuid(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QString getSupUuid() const;
    void setSupUuid(const QString &value);

    quint32 getSequence() const;
    void setSequence(const quint32 &value);

    quint8 getState() const;
    void setState(const quint8 &value);

    QString getInsertor() const;
    void setInsertor(const QString &value);

    QString getInsertTime() const;
    void setInsertTime(const QString &value);

    QString getOperater() const;
    void setOperater(const QString &value);

    QString getOperatTime() const;
    void setOperatTime(const QString &value);
    //清空
    void clear(void);
private:
    //UUID
    QString uuid;
    //组名
    QString name;
    //备注
    QString description;
    //上级组UUID
    QString supUuid;
    //排序
    qint32 sequence;
    //组状态
    quint8 state;
    //添加人
    QString insertor;
    //添加时间
    QString insertTime;
    //操作人
    QString operater;
    //操作时间
    QString operatTime;
};

#endif // CSCLIENTGROUP_H
