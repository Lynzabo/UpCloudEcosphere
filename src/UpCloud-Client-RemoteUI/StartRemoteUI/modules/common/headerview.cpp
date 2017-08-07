#include "headerview.h"

HeaderView::HeaderView(Qt::Orientation orientation, QWidget *parent)
    : QHeaderView(orientation, parent)
    , m_isOn(false)
{
    // set clickable by default
    setChecked(false);
}

void HeaderView::setChecked(bool checked)
{
    if (isEnabled() && m_isOn != checked)
    {
        m_isOn = checked;
        updateSection(0);
        emit headCheckBoxToggled(m_isOn);
    }
}

void HeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore();
    if (logicalIndex == 1)
    {
//        QPixmap filterPixmap(QString(":/imgs/imgs/state0"));
//        QRect target(rect.x()+rect.width()*4/5,rect.y()+ rect.height()*1/5,24,24);
//        QSize picSize(24,24);
//        QPixmap scaledPixmap = filterPixmap.scaled(picSize);
//        style()->drawItemPixmap(painter,target,Qt::AlignRight,scaledPixmap);
    }
}
void HeaderView::initStyleOption(QStyleOptionHeader *option) const
{
    option->initFrom(this);
    option->state = QStyle::State_None | QStyle::State_Raised;
    if (isEnabled())
        option->state |= QStyle::State_Enabled;
    option->section = 0;
}
void HeaderView::mousePressEvent(QMouseEvent *event)
{
    if (isEnabled() && logicalIndexAt(event->pos()) == 0)
    {
        m_isOn = !m_isOn;
        updateSection(0);
        emit headCheckBoxToggled(m_isOn);
    }
    else QHeaderView::mousePressEvent(event);
}
