#ifndef DATETIMEPICKER_H
#define DATETIMEPICKER_H

#include <QFrame>
#include <QDateTime>
namespace Ui {
class DateTimePicker;
}

class DateTimePicker : public QFrame
{
    Q_OBJECT

public:
    explicit DateTimePicker(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~DateTimePicker();
    void setDefault(const QDateTime &dateTime);
    void setCurrent(const QDateTime &dateTime);
private slots:
    void on_btn_ok_clicked();

    void on_btn_now_clicked();

    void on_btn_clear_clicked();

    void on_cb_time_currentIndexChanged(int index);

    void on_setDate(const QDate &date);
signals:
    void evt_setDateTime(const QDateTime &dateTime);
private:
    Ui::DateTimePicker *ui;
    QDateTime defaultDateTime;
    QDateTime savedateTime;
    QDate selectedDate;
};

#endif // DATETIMEPICKER_H
