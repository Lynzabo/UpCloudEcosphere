#include "datetimeedit.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDesktopWidget>
//DateTimeEdit::DateTimeEdit(QWidget *parent) :
//    QLineEdit(parent),
//    m_PopFrame(NULL, Qt::Popup),
//  m_Popheight(0),
//  m_Screenbound(50)
//{
//}

DateTimeEdit::DateTimeEdit(QWidget *parent):
        QDateTimeEdit(parent),
            m_PopFrame(NULL, Qt::Popup),
          m_Popheight(0),
          m_Screenbound(50)
{
    QLineEdit *edit = new QLineEdit;
    QStyleOptionComboBox optCombo;
    optCombo.init(this);
    optCombo.editable = true;
    optCombo.subControls = QStyle::SC_ComboBoxEditField;
    edit->setGeometry(this->style()->subControlRect(QStyle::CC_ComboBox, &optCombo,
                                                 QStyle::SC_ComboBoxEditField, this));

    m_PopFrame.setDefault(dateTime());
//    connect(this,SIGNAL(dateChanged(QDate)),m_PopFrame,this,
    connect(&m_PopFrame,&DateTimePicker::evt_setDateTime,this,&DateTimeEdit::setDateTime);
}

void DateTimeEdit::showPopup()
{
    m_PopFrame.setCurrent(dateTime());
    QRect rec = QRect(geometry());

    //QPoint p = this->mapToGlobal(QPoint(0,rec.height()));
    //QRect rec2(p , p + QPoint(rec.width(), rec.height()));

    // get the two possible list points and height
    QRect screen = QApplication::desktop()->screenGeometry(this);
    QPoint above = this->mapToGlobal(QPoint(0,0));
    int aboveHeight = above.y() - screen.y();
    QPoint below = this->mapToGlobal(QPoint(0,rec.height()));
    int belowHeight = screen.bottom() - below.y();

    // first activate it with height 1px to get all the items initialized
    QRect rec2;
    rec2.setTopLeft(below);
    rec2.setWidth(rec.width());
    rec.setHeight(1);
    m_PopFrame.setGeometry(rec2);
    m_PopFrame.raise();
    m_PopFrame.show();
    QCoreApplication::processEvents();

    // determine rect
    int contheight = 0;//m_PopItems->count()*m_PopItems->sizeHintForRow(0) + 4; // +4 - should be determined by margins?
    belowHeight = abs(belowHeight)-m_Screenbound;//min(abs(belowHeight)-m_Screenbound, contheight);
    aboveHeight = abs(aboveHeight)-m_Screenbound;//min(abs(aboveHeight)-m_Screenbound, contheight);

    if (m_Popheight > 0) // fixed
    {
        rec2.setHeight(m_Popheight);
    }
    else // dynamic
    {
        // do we use below or above
        if (belowHeight==contheight || belowHeight>aboveHeight)
        {
            rec2.setTopLeft(below);
            //rec2.setHeight(belowHeight);
        }
        else
        {
            rec2.setTopLeft(above - QPoint(0,aboveHeight));
            //rec2.setHeight(aboveHeight);
        }
    }

    m_PopFrame.setGeometry(rec2);
    m_PopFrame.raise();
    m_PopFrame.show();
}

void DateTimeEdit::hidePopup()
{
    m_PopFrame.hide();
}

