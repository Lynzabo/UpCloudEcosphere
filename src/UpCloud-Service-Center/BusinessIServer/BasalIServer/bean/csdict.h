#ifndef CSDICT_H
#define CSDICT_H
#include <QtCore>

/**
 * @brief The CsDict class  中心服务器数据字典表
 */
class CsDict
{
public:
    CsDict();
    QString getUuid() const;
    void setUuid(const QString &value);

    QString getCode() const;
    void setCode(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    qint32 getSequence() const;
    void setSequence(const qint32 &value);

    quint8 getState() const;
    void setState(const quint8 &value);

    QString getInsertor() const;
    void setInsertor(const QString &value);

    QString getInsertTime() const;
    void setInsertTime(const QString &value);

    QString getOperater() const;
    void setOperater(const QString &value);

    QString getOperaTime() const;
    void setOperaTime(const QString &value);

    QString getSupUuid() const;
    void setSupUuid(const QString &value);

private:
    //UUID
    QString uuid;
    //字典编码
    QString code;
    //字典名称
    QString name;
    //备注信息
    QString description;
    //字典顺序
    qint32 sequence;
    //上级字典编码
    QString supUuid;
    //字典状态
    quint8 state;
    //添加人
    QString insertor;
    //添加时间
    QString insertTime;
    //操作人
    QString operater;
    //操作时间
    QString operaTime;
};

#endif // CSDICT_H
