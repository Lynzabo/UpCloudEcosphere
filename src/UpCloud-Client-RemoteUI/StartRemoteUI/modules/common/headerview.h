#ifndef HEADERVIEW_H
#define HEADERVIEW_H

#include <QWidget>
#include <QHeaderView>
#include <QPainter>
#include <QMouseEvent>
class HeaderView : public QHeaderView
{
    Q_OBJECT
public:
    explicit HeaderView(Qt::Orientation orientation, QWidget *parent = 0);

    void setChecked(bool checked);

signals:
    void headCheckBoxToggled(bool checked);

protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
    void mousePressEvent(QMouseEvent *event);

    bool m_isOn;

    void initStyleOption(QStyleOptionHeader *option) const;
signals:

public slots:
};

#endif // HEADERVIEW_H
