#include "adddictwidget.h"
#include "ui_adddictwidget.h"
#include "modules/common/uihelper.h"
#include <QMessageBox>
AddDictWidget::AddDictWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddDictWidget)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_ShowModal,true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    initWindow();
}

AddDictWidget::~AddDictWidget()
{
    delete ui;
}

void AddDictWidget::setDictInfo(const QString &name, CsDict *dict, const QList<qint32> &sequenceList, bool flg)
{
    m_dict = dict;
    ui->lab_sup_name->setText(name);
    m_flg = flg;
    m_sequenceList = sequenceList;
    if(flg) {
        ui->l_code->setText(dict->getCode());
        ui->l_description->setText(dict->getDescription());
        ui->l_name->setText(dict->getName());
        ui->cb_state->setCurrentIndex(dict->getState() - 1 );
        QDateTime date = QDateTime::fromString(dict->getInsertTime(),"yyyy-MM-dd HH:mm:ss");
        ui->dte_insert_time->setDateTime(date);
        ui->lab_inserter->setText(dict->getInsertor());
        ui->spin_sequence->setValue(dict->getSequence());
        ui->lab_insert_time->setText(dict->getInsertTime());

    }
    else {
        QDateTime date = QDateTime::currentDateTime();
        ui->dte_insert_time->setDateTime(date);
        ui->lab_inserter->setText("zjy");

        //获取最大值
        auto maxSequence = [&]()->int{
                if(sequenceList.size() == 0) {
                return -1;
    }
                qint32 max = sequenceList.at(0);
                for(int i = 0; i < sequenceList.size(); ++i)
        {
            qint32 sequence = sequenceList.at(i);
            if(max < sequence) {
                max = sequence;
            }
        }
        return max;
    };
    int max = maxSequence();
    ui->spin_sequence->setValue(max + 1);
    ui->lab_insert_time->setText(date.toString("yyyy-MM-dd HH:mm:ss"));
}
}

void AddDictWidget::loadComboBoxText()
{
    QStringList text;
    text << tr("可用") << tr("unUse");
    QStringList value;
    value << "1" << "2";
    ui->cb_state->setShowInfo(text,value);
}

void AddDictWidget::on_btn_save_clicked()
{
    (*m_dict).setCode(ui->l_code->text());
    (*m_dict).setName(ui->l_name->text());
    (*m_dict).setDescription(ui->l_description->text());
    (*m_dict).setState((quint8)ui->cb_state->currentValue().toInt());
    (*m_dict).setInsertTime(ui->dte_insert_time->dateTime().toString("yyyy-MM-dd HH:mm:ss"));
    (*m_dict).setSequence((quint16)ui->spin_sequence->text().toInt());
    qint32 seqence = ui->spin_sequence->value();
    int flg;
    if(m_sequenceList.contains(seqence)) {
        QString errorStr;errorStr.clear();
        //添加字典，防止字典顺序重复
        if(!m_flg) {
            UIHelper::ShowMessageBoxError(tr("字典顺序重复，请重新填写"));
            return;
        }
        //编辑字典，防止字典顺序重复
        flg  = UIHelper::ShowMessageBoxQuesion(tr("字典顺序已有数据，你确定要互换顺序吗?"));
        if(!flg ) {
            return;
        }
    }
    emit evt_ok(flg);
    this->deleteLater();
}

void AddDictWidget::on_btn_quit_clicked()
{
    this->deleteLater();
}

void AddDictWidget::initWindow()
{
    ui->spin_sequence->setRange(1,0xfe);
    loadComboBoxText();
}
void AddDictWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void AddDictWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void AddDictWidget::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}
void AddDictWidget::on_btn_menu_cancel_clicked()
{
    this->deleteLater();
}
