#include "editgroupwidget.h"
#include "ui_editgroupwidget.h"

EditGroupWidget::EditGroupWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditGroupWidget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_ShowModal,true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    loadComboBox();
}

EditGroupWidget::~EditGroupWidget()
{
    delete ui;
}

void EditGroupWidget::setShowGroupInfo(const CsClientGroup &group)
{
    m_group = group;
}

void EditGroupWidget::on_btn_save_clicked()
{
    (*m_params)["name"] = ui->l_name->text();
    (*m_params)["description"] = ui->te_description->toPlainText();
    (*m_params)["state"] = ui->cb_state->currentValue().toString();
    emit evt_saveInfo();
    deleteLater();
}

void EditGroupWidget::on_btn_quit_clicked()
{
    m_params = 0;
    deleteLater();
}

void EditGroupWidget::showEvent(QShowEvent *event)
{
    ui->l_name->setText(m_group.getName());
    // TODO 这里数据不全 需要修正
//    int index = m_group.getState();
    ui->cb_state->setCurrentIndex(0);
    ui->te_description->setText(m_group.getDescription());
    ui->l_supUuid->setText(m_group.getSupUuid());
    ui->l_insertor->setText(m_group.getInsertor());
    ui->l_dateTime->setText(m_group.getInsertTime());
}

void EditGroupWidget::getParams(QVariantMap* params)
{
    m_params = params;
}

void EditGroupWidget::loadComboBox()
{
    QStringList text;
    text << tr("可用") << tr("禁用");
    QStringList value;
    value << tr("1") << tr("2");
    ui->cb_state->setShowInfo(text,value);
}

void EditGroupWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void EditGroupWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void EditGroupWidget::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void EditGroupWidget::on_btn_menu_cancel_clicked()
{
    m_params = 0;
    deleteLater();
}
