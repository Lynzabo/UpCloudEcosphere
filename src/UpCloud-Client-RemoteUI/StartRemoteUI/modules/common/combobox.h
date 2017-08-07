#ifndef COMBOBOX_H
#define COMBOBOX_H
#include <QtCore>
#include <QComboBox>
#include <QListView>

class ComboBox : public QComboBox
{
    Q_OBJECT
public:
    ComboBox(QWidget *parent = 0);
    ~ComboBox();
    //设置文本对应的后台使用的值
    void setShowInfo(const QList<QVariantMap> & mapInfo);
    //设置文本以及文本对应的后台使用的值
    void setShowInfo(const QStringList &textList,const QStringList &valueList);
    //设置文本-值
    void setShowInfo(const QStringList &info);
    //设置只有文本
    void setItemsText(const QStringList &textList);
    //获取索引对应后台使用的值
    QVariant itemTextValue(int index);
    //获取文本对应后台使用的值
    QVariant itemTextValue(const QString &text);
    //修改文本对应的值
    void updateTextValue(const QString &text, const QVariant &value);
    //增加下拉项目 (在尾部)
    void addTextValue(const QString &text, const QVariant &value);
    //增加下拉项目 (在指定的位置)
    void addTextValue(int pos,const QString &text, const QVariant &value);
    //删除索引对应的项目
    void delTextValue(int index);
    //删除文本对应的项目
    void delTextValue(const QString &text);
    //获取当前的值
    QVariant currentValue();
    //设置第一条的值是否有效
    void setFirstVoild(bool flg);
signals:
    void indexChanged(int index);
private slots:
    void indexChangedSlot(int index);
    void activeChanged();

private:
    QList<QVariantMap> m_listInfo;
    bool m_firstVoild;
    QListView* temLv;
};

#endif // COMBOBOX_H
