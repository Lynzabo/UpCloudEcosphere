#include "rmessagebox.h"
#include "ui_rmessagebox.h"
#include "uihelper.h"
RMessageBox::RMessageBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RMessageBox)
{
    ui->setupUi(this);
    //设置窗体关闭时自动释放内存
    this->setAttribute(Qt::WA_DeleteOnClose);
    //初始化设置窗口基本数据
    initWindow();
}

RMessageBox::~RMessageBox()
{
    delete ui;
}

void RMessageBox::setMessage(const QString &msg, RMessageBox::Type type)
{
    if (type == RMessageBox::INFO) {
        ui->l_icon->setStyleSheet("border-image: url(:/core/imgs/imgs/messagebox_success);");
        ui->gb_opera_confirm->hide();
        ui->gb_opera_warn->hide();
        ui->l_title->setText("提示");
        this->setWindowTitle("提示");
    } else if (type == RMessageBox::QUESTION) {
        ui->l_icon->setStyleSheet("border-image: url(:/core/imgs/imgs/messagebox_question);");
        ui->gb_opera_alert->hide();
        ui->gb_opera_warn->hide();
        ui->l_title->setText("询问");
        this->setWindowTitle("询问");
    }else if (type == RMessageBox::WARN) {
        ui->l_icon->setStyleSheet("border-image: url(:/core/imgs/imgs/messagebox_question);");
        ui->gb_opera_alert->hide();
        ui->gb_opera_confirm->hide();
        ui->l_title->setText("警告");
        this->setWindowTitle("警告");
    } else if (type == RMessageBox::ERR) {
        ui->l_icon->setStyleSheet("border-image: url(:/core/imgs/imgs/messagebox_error);");
        ui->gb_opera_confirm->hide();
        ui->gb_opera_warn->hide();
        ui->l_title->setText("错误");
        this->setWindowTitle("错误");
    }
    ui->l_content->setText(msg);
    //窗体居中显示
    UIHelper::FormInCenter(this);
}

void RMessageBox::initWindow()
{
    this->mousePressed = false;
    //设置窗体标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    //关联关闭按钮
    connect(ui->btn_warn_exit, SIGNAL(clicked()), this, SLOT(on_warn_exit()));
    //connect(ui->btn_menu_cancel, SIGNAL(clicked()), this, SLOT(close()));
    //alert
    //connect(ui->btn_alert_ok, SIGNAL(clicked()), this, SLOT(close()));
    //connect(ui->btn_confirm_cancel, SIGNAL(clicked()), this, SLOT(close()));
    //connect(ui->btn_alert_ok, SIGNAL(clicked()), this, SLOT(close()));
    //窗体居中显示
    UIHelper::FormInCenter(this);
}

void RMessageBox::on_warn_exit()
{
    //自定义数字
    done(2);
    this->close();
}

void RMessageBox::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void RMessageBox::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void RMessageBox::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}
