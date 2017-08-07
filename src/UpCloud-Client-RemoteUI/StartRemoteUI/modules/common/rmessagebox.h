#ifndef RMESSAGEBOX_H
#define RMESSAGEBOX_H

#include <QtWidgets>
#include <QtCore>

namespace Ui {
class RMessageBox;
}

class RMessageBox : public QDialog
{
    Q_OBJECT

public:
    //MessageBox类型
    enum Type {
        INFO,
        QUESTION,
        ERR,
        WARN
    };
    explicit RMessageBox(QWidget *parent = 0);
    ~RMessageBox();
    void setMessage(const QString &msg, RMessageBox::Type type = RMessageBox::INFO);

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
private:
    /**
     * @brief initWindow    初始化窗口基本数据
     */
    void initWindow();
private slots:
    void on_warn_exit();
private:
    Ui::RMessageBox *ui;
    QPoint mousePoint;
    //鼠标是否按下
    bool mousePressed;
};

#endif // RMESSAGEBOX_H
