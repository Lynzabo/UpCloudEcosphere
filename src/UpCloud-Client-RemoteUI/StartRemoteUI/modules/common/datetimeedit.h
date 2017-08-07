#ifndef DATETIMEEDIT_H
#define DATETIMEEDIT_H

#include <QDateTimeEdit>
#include "datetimepicker.h"
#include <QLineEdit>
#include <QStyleOptionComboBox>
#include <QMouseEvent>
class DateTimeEdit : public QDateTimeEdit
{
    Q_OBJECT
public:
    explicit DateTimeEdit(QWidget *parent = 0);
    void showPopup();
    void hidePopup();

    void mousePressEvent(QMouseEvent *event)
    {
        showPopup();
    }
signals:

public slots:
private:
    //下拉面板
    DateTimePicker m_PopFrame;
    //弹出列表高度
    int m_Popheight;
    //lower/upper screen bound
    int m_Screenbound;
};

#endif // DATETIMEEDIT_H
