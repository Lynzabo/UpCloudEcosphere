#include "treenode.h"

TreeNode::TreeNode()
{

}
QString TreeNode::getUuid() const
{
    return uuid;
}

void TreeNode::setUuid(const QString &value)
{
    uuid = value;
}
QString TreeNode::getName() const
{
    return name;
}

void TreeNode::setName(const QString &value)
{
    name = value;
}
QString TreeNode::getDescription() const
{
    return description;
}

void TreeNode::setDescription(const QString &value)
{
    description = value;
}
bool TreeNode::getIsGroup() const
{
    return isGroup;
}

void TreeNode::setIsGroup(bool value)
{
    isGroup = value;
}
bool TreeNode::getIsParent() const
{
    return isParent;
}

void TreeNode::setIsParent(bool value)
{
    isParent = value;
}
QString TreeNode::getParentUuid() const
{
    return parentUuid;
}

void TreeNode::setParentUuid(const QString &value)
{
    parentUuid = value;
}
QModelIndex TreeNode::getIndex() const
{
    return index;
}

void TreeNode::setIndex(const QModelIndex &value)
{
    index = value;
}
qint32 TreeNode::getSequence() const
{
    return sequence;
}

void TreeNode::setSequence(const qint32 &value)
{
    sequence = value;
}









