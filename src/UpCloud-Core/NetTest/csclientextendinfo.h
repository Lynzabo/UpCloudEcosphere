#ifndef CSCLIENTEXTENDINFO_H
#define CSCLIENTEXTENDINFO_H
#include <QtCore>

/**
 * @brief The CsClientExtendInfo class
 * 存放节点补充信息。比如节点描述信息
 *注意：根据心跳策略确定增加/删除该客户端信息
 */


class CsClientExtendInfo
{

private:
    //UUID
    QString uuid;
    //客户端UUID
    QString clientUuid;
    //客户端描述信息
    QString description;
    //客户端类型
    QChar   type;
    //所属组UUID
    QString groupUuid;
public:
    CsClientExtendInfo();

    QString getUuid() const;
    void setUuid(const QString &value);

    QString getClientUuid() const;
    void setClientUuid(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QChar getType() const;
    void setType(const QChar &value);

    QString getGroupUuid() const;
    void setGroupUuid(const QString &value);
};

#endif // CSCLIENTEXTENDINFO_H
