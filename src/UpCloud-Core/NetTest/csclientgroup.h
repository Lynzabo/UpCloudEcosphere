#ifndef CSCLIENTGROUP_H
#define CSCLIENTGROUP_H

#include <QtCore>

/**
 * @brief The CsClientGroup class
 * 节点服务器组维护
 */
class CsClientGroup
{

private:
    //UUID
    QString uuid;
    //组名
    QString name;
    //备注
    QString description;
    //上级组UUID
    QString parentUuid;
    //排序
    quint32 sequence;
public:
    CsClientGroup();



    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QString getParentUuid() const;
    void setParentUuid(const QString &value);

    quint32 getSequence() const;
    void setSequence(const quint32 &value);
    QString getUuid() const;
    void setUuid(const QString &value);
};

#endif // CSCLIENTGROUP_H
