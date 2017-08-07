#ifndef DIRDICTWIDGET_H
#define DIRDICTWIDGET_H

#include <QWidget>
#include <QtCore>
#include <QLineEdit>
#include <QSplitter>
#include <QPushButton>
#include "dicttree.h"
#include "selectdictwidget.h"
namespace Ui {
class DirDictWidget;
}

class DirDictWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DirDictWidget(QWidget *parent = 0);
    ~DirDictWidget();

private:
    void initWindow();
private slots:
    //加载查询字典界面
    void loadSelectWidget(const QString &uuid);


protected:
    void mouseMoveEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
    void showEvent(QShowEvent *event);
private:
    void setBtnPos();
    void setBtnIcon();

private slots:
    void slotClickedBtn();
    void slotSplitterMoved(int pos, int index);



private:
    Ui::DirDictWidget *ui;
    DictTree* dictTree;
    SelectDictWidget* selectDict;
    QSplitter* splitter;

    int dictMinW;
    int treeMaxW;

    QPushButton *pushButton;
    QIcon leftIcon;
    QIcon rightIcon;

    QPoint dragPosition;
    bool bPressFlag;

};

#endif // DIRDICTWIDGET_H
