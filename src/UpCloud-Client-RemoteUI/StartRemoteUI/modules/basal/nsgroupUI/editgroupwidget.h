#ifndef EDITGROUPWIDGET_H
#define EDITGROUPWIDGET_H

#include <QWidget>
#include <QtCore>
#include <QMouseEvent>
#include "modules/common/combobox.h"
#include "../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/cscgroup.h"
namespace Ui {
class EditGroupWidget;
}

class EditGroupWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EditGroupWidget(QWidget *parent = 0);
    ~EditGroupWidget();
    void setShowGroupInfo(const CsClientGroup &group);
    void getParams(QVariantMap *params);
    void loadComboBox();
signals:
    void evt_saveInfo();
protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
private slots:
    void on_btn_save_clicked();

    void on_btn_quit_clicked();
    void on_btn_menu_cancel_clicked();

private:
    void showEvent(QShowEvent *event);
private:
    Ui::EditGroupWidget *ui;
    QVariantMap* m_params;
    CsClientGroup m_group;

    bool mousePressed;
    QPoint mousePoint;
};

#endif // EDITGROUPWIDGET_H
