#include "combobox.h"
ComboBox::ComboBox(QWidget *parent)
{
    setParent(parent);
    m_listInfo.clear();
    temLv = new QListView(this);
    this->setMaxVisibleItems(20);
    this->setView(temLv);
    m_firstVoild = true;
    connect(this,SIGNAL(currentIndexChanged(int)),this,SLOT(indexChangedSlot(int)));
    connect(this,SIGNAL(currentIndexChanged(int)),this,SLOT(activeChanged()));
}

ComboBox::~ComboBox()
{
    temLv->deleteLater();
}

void ComboBox::setShowInfo(const QList<QVariantMap> &mapInfo)
{
    if(&mapInfo != &m_listInfo)
    {
        m_listInfo = mapInfo;
    }
    for(int i = 0;i < m_listInfo.size(); ++i)  {
        this->addItem(m_listInfo.at(i).keys().at(0));
    }

}

void ComboBox::setShowInfo(const QStringList &textList, const QStringList &valueList)
{
    if(textList.size() != valueList.size()) {
        return;
    }
    for(int i = 0;i < textList.size(); ++i)
    {
        QVariantMap info;
        info.insert(textList.at(i),valueList.at(i));
        m_listInfo.append(info);
    }
    this->setShowInfo(m_listInfo);
}

void ComboBox::setShowInfo(const QStringList &info)
{
    if(info.size() > 2) {
        return;
    }
    QVariantMap tem;
    tem.insert(info.at(0),info.at(1));
    m_listInfo.append(tem);
    this->setShowInfo(m_listInfo);
}

void ComboBox::setItemsText(const QStringList &textList)
{
    m_listInfo.clear();
    foreach(const QString& text,textList) {
        QVariantMap info;
        info.insert(text,text);
        m_listInfo.append(info);
    }
    if(m_firstVoild) {
        QList<QVariantMap>::iterator item = m_listInfo.begin();
        (*item)[textList.at(0)] = "";
    }
    this->addItems(textList);
}

QVariant ComboBox::itemTextValue(int index)
{
    return m_listInfo.at(index).values().at(0);
}

QVariant ComboBox::itemTextValue(const QString &text)
{
    foreach(const QVariantMap &info,m_listInfo) {
        if(info.keys().at(0) == text) {
            return info.value(text);
        }
    }
}

void ComboBox::addTextValue(const QString &text, const QVariant &value)
{
    QVariantMap info;
    info.insert(text,value);
    m_listInfo.insert(m_listInfo.size(),info);
    this->clear();
    this->setShowInfo(m_listInfo);
}

void ComboBox::addTextValue(int pos, const QString &text, const QVariant &value)
{
    QVariantMap info;
    info.insert(text,value);
    m_listInfo.insert(pos,info);
    this->clear();
    this->setShowInfo(m_listInfo);
}

void ComboBox::delTextValue(int index)
{
    this->removeItem(index);
    m_listInfo.removeAt(index);
}

void ComboBox::delTextValue(const QString &text)
{
    foreach(const QVariantMap & info,m_listInfo)
    {
        if(info.keys().at(0) == text) {
            int index = m_listInfo.indexOf(info);
            delTextValue(index);
            break;
        }
    }
}

QVariant ComboBox::currentValue()
{
    int index = currentIndex();
    return itemTextValue(index);
}

void ComboBox::setFirstVoild(bool flg)
{
    m_firstVoild = flg;
}

void ComboBox::updateTextValue(const QString &text,const QVariant &value)
{
    for(QList<QVariantMap>::iterator item = m_listInfo.begin();
        item != m_listInfo.end(); ++item)
    {
        if(item->keys().at(0) == text)
        {
            (*item)[text] = value;
            break;
        }
    }
    this->clear();
    this->setShowInfo(m_listInfo);
}

void ComboBox::indexChangedSlot(int index)
{
    qDebug() << index;
    emit
    indexChanged(index);
}

void ComboBox::activeChanged()
{
    //TODO 动态删除功能 暂时不加 动态描绘 动态置顶
    QString text = this->itemText(0);

}

