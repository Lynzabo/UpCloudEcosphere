#include "filedirwidget.h"
#include "ui_filedirwidget.h"
#include <QSocketNotifier>
#include <QTimer>
#include <QHeaderView>
FileDirWidget::FileDirWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileDirWidget)
{
    ui->setupUi(this);
    m_flg = 4;
    m_defaultDir.clear();
    this->setAttribute(Qt::WA_ShowModal,true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    par.port = 22;
    par.userName = "root";
    par.password = "qwer1234";
    par.host = "10.0.0.2";
    par.timeout = 500;

    par.authenticationType = QSsh::SshConnectionParameters::AuthenticationTypePassword;
    con = new QSsh::SshConnection(par);
    connect(con,&QSsh::SshConnection::connected,this,&FileDirWidget::on_sshcon);
    //    connect(con,&QSsh::SshConnection::dataAvailable,[this](const QString & mse){this->ui->
    //   lineEdit->setText(mse);});
    connect(con,&QSsh::SshConnection::disconnected,[this](){this->setWindowTitle("SSH disconnect");});
    con->connectToHost();
    initWindow();
}

FileDirWidget::~FileDirWidget()
{
    delete ui;
    if (nullptr != con)
    {
        con->deleteLater();
    }
}

void FileDirWidget::on_selectDirs(const QModelIndex &index)
{
    QString dirName = index.data().toString();
    if (nullptr != con)
    {
        if (con->state() == QSsh::SshConnection::Connected)
        {
            QString str = "cd " + dirName + ";" + "ls -l |grep ^d";
            str += "\n";
            m_shell.data()->write(str.toStdString().c_str());
        }
    }
    m_flg = 0;
}

void FileDirWidget::initWindow()
{

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setShowGrid(false);
    ui->tableWidget->setFrameShape(QFrame::NoFrame);
    ui->tableWidget->verticalHeader()->setVisible(false);
    connect(ui->tableWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_selectDirs(QModelIndex)));
//    QTimer::singleShot(2000,this,SLOT(on_selectCurDir()));

}

void FileDirWidget::on_selectCurDir()
{
    if (nullptr != con)
    {
        if (con->state() == QSsh::SshConnection::Connected)
        {
            QString str = "cd /;ls -l |grep ^d";
//            if(!m_defaultDir.isEmpty()) {
//                str.clear();
//                str = "cd " + m_defaultDir + ";ls -l |grep ^d";
//            }
            str += "\r\n";
            m_shell.data()->write(str.toStdString().c_str());
            //            qDebug() << str;
        }
    }
}


void FileDirWidget::on_sshcon()
{
    m_shell = con->createRemoteShell();
    //    connect(m_shell.data(),&QSsh::SshRemoteProcess::started,[this](){this->ui->lineEdit->append("SshRemoteProcess start succsess");});
    connect(m_shell.data(),&QSsh::SshRemoteProcess::readyReadStandardOutput,[this](){this->on_showDirsList(QString(this->m_shell.data()->readAllStandardOutput()));
    });
    connect(m_shell.data(),&QSsh::SshRemoteProcess::readyRead,[this](){this->on_showDirsList(QString(this->m_shell.data()->readAllStandardOutput()));});
    //    connect(m_shell.data(),&QSsh::SshRemoteProcess::readyReadStandardError,[this](){this->showDir(QString(this->m_shell.data()->readAll()));});
    //    connect(m_shell.data(),&QSsh::SshRemoteProcess::closed,[this](){this->ui->lineEdit->append("SshRemoteProcess stop");});
    m_shell.data()->start();
}

void FileDirWidget::on_btn_save_clicked()
{
    QString dir = ui->lineEdit->text().trimmed();
    emit evt_selectDir(dir);
    con->disconnectFromHost();
    this->deleteLater();
}

void FileDirWidget::on_btn_quit_clicked()
{
    con->disconnectFromHost();

    this->deleteLater();
}

void FileDirWidget::on_btn_back_clicked()
{
    if (nullptr != con)
    {
        if (con->state() == QSsh::SshConnection::Connected)
        {
            QString str("cd ..;ls -l |grep ^d");
            str += "\r\n";
            m_shell.data()->write(str.toStdString().c_str());

        }
    }
    m_flg = 0;
}

void FileDirWidget::on_showDirsList(const QString &dirList)
{
    qDebug() <<"dirList ::::" << dirList;
    QStringList dirs = dirList.split("\r\n");
    QString begin = dirs.at(0);
    //调试专用
    /* if(dirs.at(0) == "cd /;ls -l |grep ^d") {
        dirs.removeFirst();
        if(dirs.size() <= 0) {
            return;
        }
        m_flg = 2;
    }
    //登录信息不展示
    else*/ if(begin.left(11) == "Last login:") {
        return;
    }
    //查询信息信号开始
    else if(begin.left(2) == "cd" || begin.left(2) == "ls")
    {
        //每次查询清空列表

        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(0);
            m_flg = 1;
    }
    else if(dirs.contains("pwd")) {
        ui->lineEdit->setText(dirs.at(1));
        return;
    }
    else if(begin.left(1) == "[") {

        //如果该是显示文件夹列表信息，遇到结束标志，表示，列表为空
        if(m_flg == 1){
            ui->tableWidget->clearContents();
            ui->tableWidget->setRowCount(0);
            QString str("pwd");
            str += "\r\n";
            m_shell.data()->write(str.toStdString().c_str());
            m_flg = 0;
        }
        //否则一定是登录信息显示完成标志，则查询当前目录信息
        else {
            QTimer::singleShot(100,this,SLOT(on_selectCurDir()));
        }
        return;
    }
    //显示文件夹列表
    if(m_flg == 1) {
        int preRow = ui->tableWidget->rowCount() - 1;
        ui->tableWidget->setRowCount(dirs.size()  + preRow);
        int rowNum = 0;
        for(int i = 0;i < dirs.size(); ++i) {
            QString info = dirs.at(i);
            QStringList itemInfo = info.split(" ");
            QString firstStr = itemInfo.at(0);
            if(firstStr.left(1) == "[" ) {
                QString str("pwd");
                str += "\r\n";
                m_shell.data()->write(str.toStdString().c_str());
                m_flg = 0;
                return;
            }
            //忽略所有错误信息，只要文件信息列表
            if(firstStr.left(1) != "d" ) {
                continue;
            }
            QTableWidgetItem* item = new QTableWidgetItem;
            item->setText(itemInfo.last());
            ui->tableWidget->setItem(preRow + rowNum++,0,item);
            //            qDebug() << item->text();
        }
    }
}

QString FileDirWidget::defaultDir() const
{
    return m_defaultDir;
}

void FileDirWidget::setDefaultDir(const QString &defaultDir)
{
    m_defaultDir = defaultDir;
}
void FileDirWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void FileDirWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void FileDirWidget::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void FileDirWidget::on_btn_menu_cancel_clicked()
{
    con->disconnectFromHost();

    this->deleteLater();
}
