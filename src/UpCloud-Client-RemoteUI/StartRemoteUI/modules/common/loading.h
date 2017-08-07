#ifndef LOADING_H
#define LOADING_H

#include <QWidget>

namespace Ui {
class Loading;
}

class Loading : public QWidget
{
    Q_OBJECT

public:
    explicit Loading(QWidget *parent = 0);
    ~Loading();
    void setMsg(const QString &msg);
protected:
    void paintEvent(QPaintEvent *e);
private:
    /**
     * @brief initWindow    初始化窗口基本数据
     */
    void initWindow();

private:
    Ui::Loading *ui;
    QWidget *widget;
};

#endif // LOADING_H
