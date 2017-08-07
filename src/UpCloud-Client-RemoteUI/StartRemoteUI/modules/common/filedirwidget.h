#ifndef FILEDIRWIDGET_H
#define FILEDIRWIDGET_H

#include <QWidget>
#include <qsharedpointer.h>
#include <QMouseEvent>
#include "../include/ssh/sshremoteprocess.h"
#include "../include/ssh/sshconnection.h"
namespace Ui {
class FileDirWidget;
}

class FileDirWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileDirWidget(QWidget *parent = 0);
    ~FileDirWidget();
    void initWindow();

    QString defaultDir() const;
    void setDefaultDir(const QString &defaultDir);
protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

private slots:
    //查询当前目录所有文件夹
    void on_selectCurDir();
    void on_sshcon();
    //查询指定的目录所有文件夹
    void on_selectDirs(const QModelIndex &index);

    void on_btn_save_clicked();

    void on_btn_quit_clicked();

    void on_btn_back_clicked();
    //在界面上显示所有文件夹及当前绝对路径
    void on_showDirsList(const QString &dirList);
    void on_btn_menu_cancel_clicked();

signals:
    void evt_selectDir(const QString &dir);
private:
    Ui::FileDirWidget *ui;
    bool errorLsNum;
    QSsh::SshConnectionParameters par;
    QSsh::SshConnection * con;
    QSharedPointer<QSsh::SshRemoteProcess> m_shell;
    int m_flg;
    bool mousePressed;
    QPoint mousePoint;
    QString m_defaultDir;
};

#endif // FILEDIRWIDGET_H
