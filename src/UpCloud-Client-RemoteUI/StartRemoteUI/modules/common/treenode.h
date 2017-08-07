#ifndef TREENODE_H
#define TREENODE_H
#include <QtCore>
#include "treeglobal.h"
#include <QModelIndex>
class GLOBAL_EXPORT TreeNode
{
public:
    TreeNode();
    QString getUuid() const;
    void setUuid(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    bool getIsGroup() const;
    void setIsGroup(bool value);

    bool getIsParent() const;
    void setIsParent(bool value);

    QString getParentUuid() const;
    void setParentUuid(const QString &value);

    QModelIndex getIndex() const;
    void setIndex(const QModelIndex &value);

    qint32 getSequence() const;
    void setSequence(const qint32 &value);

private:
    QString uuid;
    QString name;
    QString description;
    bool isGroup;
    bool isParent;
    QString parentUuid;
    QModelIndex index;
    qint32 sequence;
};

#endif // TREENODE_H
