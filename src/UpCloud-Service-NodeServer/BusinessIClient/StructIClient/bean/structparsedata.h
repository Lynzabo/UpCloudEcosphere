#ifndef STRUCTPARSEDATA_H
#define STRUCTPARSEDATA_H

#include <QtCore>

class StructParseData
{
public:
    StructParseData();

    enum Type {
        Insert,
        Update,
        Delete
    };

    quint32 getRef() const;
    void setRef(const quint32 &value);

    Type getType() const;
    void setType(const Type &value);

    QString getInfo() const;
    void setInfo(const QString &value);

private:
    //数据索引
    quint32 ref;
    //数据类型
    Type type;
    //数据内容
    QString info;
};

#endif // STRUCTPARSEDATA_H
