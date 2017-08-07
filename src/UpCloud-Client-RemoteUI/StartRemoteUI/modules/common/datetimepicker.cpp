#include "datetimepicker.h"
#include "ui_datetimepicker.h"

DateTimePicker::DateTimePicker(QWidget *parent, Qt::WindowFlags f) :
    QFrame(parent,f),
    ui(new Ui::DateTimePicker)
{
    ui->setupUi(this);

    connect(ui->calendarWidget,SIGNAL(clicked(QDate)),this,SLOT(on_setDate(QDate)));
}

DateTimePicker::~DateTimePicker()
{
    delete ui;
}

void DateTimePicker::setDefault(const QDateTime &dateTime)
{
    defaultDateTime = dateTime;

}

void DateTimePicker::setCurrent(const QDateTime &dateTime)
{
    ui->calendarWidget->setSelectedDate(dateTime.date());
    ui->te_time->setTime(dateTime.time());
}

void DateTimePicker::on_btn_ok_clicked()
{

   QTime time = ui->te_time->time();
   savedateTime.setDate(selectedDate);
   savedateTime.setTime(time);
   emit evt_setDateTime(savedateTime);
   hide();
}

void DateTimePicker::on_btn_now_clicked()
{
   QDateTime dateTime = QDateTime::currentDateTime();
   emit evt_setDateTime(dateTime);
   hide();
}

void DateTimePicker::on_btn_clear_clicked()
{
    //重置常用时间
    ui->cb_time->setCurrentIndex(0);

    ui->calendarWidget->setSelectedDate(defaultDateTime.date());
    ui->te_time->setTime(defaultDateTime.time());
    savedateTime = defaultDateTime;
}


void DateTimePicker::on_cb_time_currentIndexChanged(int index)
{
    if(!index) {
        return;
    }
    QString strTime = ui->cb_time->currentText();
    QTime time = QTime::fromString(strTime,"hh:mm:ss");
    ui->te_time->setTime(time);
}

void DateTimePicker::on_setDate(const QDate &date)
{

    selectedDate = date;
}

