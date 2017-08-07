#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include <QToolButton>
#include <QMouseEvent>
#include <QPainter>

class ToolButton : public QToolButton
{
    Q_OBJECT
public:
    explicit ToolButton(QWidget *parent = 0);
    /**
     * @brief setBtnPixmap  设置按钮图片
     * @param picName
     */
    void setBtnPixmap(const QString &picName);
    void setMousePress(bool mouse_press);

protected:

    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void painterInfo(int top_color, int middle_color, int bottom_color);

private:
    //鼠标是否移过
    bool mouse_over;
    //鼠标是否按下
    bool mouse_press;
signals:

public slots:
};

#endif // TOOLBUTTON_H
