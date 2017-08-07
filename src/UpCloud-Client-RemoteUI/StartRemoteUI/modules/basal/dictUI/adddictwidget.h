#ifndef ADDDICTWIDGET_H
#define ADDDICTWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include "../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/csdict.h"
namespace Ui {
class AddDictWidget;
}

class AddDictWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddDictWidget(QWidget *parent = 0);
    ~AddDictWidget();
    void setDictInfo(const QString &name, CsDict *dict, const QList<qint32> &sequenceList, bool flg);
    void loadComboBoxText();
signals:
    void evt_ok(bool flg);
protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
private slots:
    void on_btn_save_clicked();

    void on_btn_quit_clicked();
    void on_btn_menu_cancel_clicked();

private:
    void initWindow();

private:
    Ui::AddDictWidget *ui;
    CsDict* m_dict;
    QString m_name;
    //存储当前同级中已有的顺序
    QList<qint32> m_sequenceList;
    //判定是编辑，还是添加的标志
    bool m_flg;

    bool mousePressed;
    QPoint mousePoint;
};

#endif // ADDDICTWIDGET_H
