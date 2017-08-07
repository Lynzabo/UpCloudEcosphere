#ifndef STRUCTPARSEDATA_H
#define STRUCTPARSEDATA_H

#include <QtCore>

class StructParseData
{
public:
    StructParseData();

    enum Type {
        Create,
        Select,
        Insert,
        Update,
        Delete,
        Drop
    };

    quint32 getRef() const;
    void setRef(const quint32 &value);

    Type getType() const;
    void setType(const Type &value);

    QString getInfo() const;
    void setInfo(const QString &value);

    QVariantMap getParams() const;
    void setParams(const QVariantMap &value);

    void setParamsArgs(const QString&key, const QString& value);

    void clear();

private:
    //数据索引
    quint32 ref;
    //数据类型
    Type type;
    //数据内容
    QString info;
    //参数列表
    QVariantMap params;
};

#endif // STRUCTPARSEDATA_H
