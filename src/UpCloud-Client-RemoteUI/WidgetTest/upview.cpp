/**************************************************************************
**   UpCloudEcosphere
**   Copyright (c) UpCloud C/C++ development team.
**   All rights 2016 reserved.
**   Author : zhoujunying
**************************************************************************/

#include "upview.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

UpView::UpView(QWidget *parent)
{
    this->setParent(parent);
    this->setTextVisible(false);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    m_flg = true;
    m_btn_opt = new QPushButton(QIcon(":/START"),"",this);
    m_btn_opt->setStyleSheet("border-width:0px;border-radius:5px;");

    connect(m_btn_opt,SIGNAL(clicked(bool)),this,SLOT(on_start(bool)));
    m_btn_end = new QPushButton(QIcon(":/CANCEL"),"",this);
    m_btn_end->setStyleSheet("border-width:0px;border-radius:5px;");
    connect(m_btn_end,SIGNAL(clicked(bool)),this,SLOT(on_end(bool)));
    m_lab_name = new QLabel(tr("放羊的星星第一集 "),this);
    m_lab_name->setAttribute(Qt::WA_TranslucentBackground);
    QPixmap pix(":/SHRINK");
    m_lab_icon = new QLabel(this);
    m_lab_icon->setPixmap(pix);
    m_lab_icon->setAttribute(Qt::WA_TranslucentBackground);
    QFont ft;
    ft.setPointSize(12);
    ft.setBold(true);
    m_lab_name->setFont(ft);
    m_lab_size = new QLabel("",this);
    m_lab_size->setAttribute(Qt::WA_TranslucentBackground);
    ft.setBold(false);
    ft.setPointSize(9);
    m_lab_size->setFont(ft);
    m_lab_time= new QLabel("",this);
    m_lab_time->setAttribute(Qt::WA_TranslucentBackground);
    ft.setPointSize(10);
    m_lab_time->setFont(ft);
    m_upBytes  = 0;
}

UpView::~UpView()
{
    delete m_btn_end;
    delete m_btn_opt;
    delete m_lab_name;
    delete m_lab_size;
    delete m_lab_time;
    delete m_lab_icon;
}
void UpView::setProcess(float per,const QString &str,const QString &time)
{
    setValue((int)per);
    m_lab_size->setText(str);
    m_lab_time->setText(time);
}

void UpView::updateInfo(quint64 haveDown, quint64 total)
{
    QTime curTime = QTime::currentTime();
    int usedTime = m_curTime.msecsTo(curTime);
    if(usedTime < 1000 && haveDown < total) {
        return;
    }
    this->setMaximum(total);
    this->setValue(haveDown);
    double speed = (haveDown - m_upBytes) * 1000.0 / 1024/usedTime;
    quint64 fileSize = total;
    QString str = fileSizeUnit(fileSize);
    if(speed <= 0 ) {
        m_lab_time->setText("--:--:--");
        m_lab_size->setText(QString("%1%2 - 0 KB/S").arg(QString::number((double)fileSize,'g')).arg(str));
    }
    else {
        double speedSize = speed*1024.0;
        QString speedStr = speedUnit(speedSize);
        QString size = QString("%1 %2- %3 %4").arg(QString::number((double)fileSize,'g')).arg(str).arg(QString::number(speedSize,'g')).arg(speedStr);
        m_lab_size->setText(size);
        quint64 remain = (total - haveDown)*1.0 /1024 /speed;
        ulong h = (ulong)remain/3600;
        ulong m = (ulong)remain%3600/60;
        ulong s = (ulong)remain%60;
        char strTime[12] = {};
        sprintf(strTime,"%02d:%02d:%02d",h,m,s);
        QString str = QString(QLatin1String(strTime));
        m_lab_time->setText(str);
    }
    m_upBytes = haveDown;
    m_curTime = curTime;
}

void UpView::setEnd()
{

}

void UpView::setStart()
{

}

void UpView::setError()
{

}

void UpView::setFileName(const QString& name)
{
    m_fileName = name;
    m_lab_name->setText(name);
}

void UpView::initView()
{

    QHBoxLayout* lay = new QHBoxLayout;
    QVBoxLayout* lay_name_size = new QVBoxLayout;
    QHBoxLayout* lay_icon_name = new QHBoxLayout;
    lay_icon_name->addWidget(m_lab_icon);
    lay_icon_name->addStretch(10);
    lay_icon_name->addWidget(m_lab_name);

    lay_name_size->addLayout(lay_icon_name);
    lay_name_size->addStretch(15);
    lay_name_size->addWidget(m_lab_size);

    QHBoxLayout* lay_time = new QHBoxLayout;
    lay_time->addWidget(m_lab_time);
    QHBoxLayout* lay_btn = new QHBoxLayout;;
    lay_btn->addWidget(m_btn_opt);
    m_btn_opt->setMaximumWidth(25);
    lay_btn->addStretch(20);
    lay_btn->addWidget(m_btn_end);
    m_btn_end->setMaximumWidth(25);
    lay->addLayout(lay_name_size);
    lay->addStretch(150);
    lay->addLayout(lay_time);
    lay->addStretch(15);
    lay->addLayout(lay_btn);

    this->setStyleSheet("QProgressBar{border: 0px solid grey;border-radius: 5px;background-color: #FFFFFF;}"
                        "QProgressBar::chunk{background-color: #05B8CC;width: 20px;}"
                        "QProgressBar{border: 0px solid grey;border-radius: 5px;text-align: center;}");
    this->setLayout(lay);
    m_curTime = QTime::currentTime();
}

void UpView::endDown()
{
    m_btn_opt->setIcon(QIcon(":/START"));
    QString str = m_lab_size->text();
    str.resize(str.lastIndexOf("-"));
    m_lab_size->setText(str);
    m_lab_time->setText("");
}

void UpView::pauseDown()
{
    m_btn_opt->setIcon(QIcon(":/START"));
    m_lab_time->setText("--:--:--");
}

void UpView::on_end(bool flg)
{
    Q_UNUSED(flg)
//    this->hide();
    emit evt_end(this);
    //发出终止信号
    //TODO
}

void UpView::on_start(bool flg)
{
    Q_UNUSED(flg)
    if(m_flg) {
        m_btn_opt->setIcon(QIcon(":/START"));
        QString str = m_lab_size->text();
        str.resize(str.lastIndexOf("-"));
        m_lab_size->setText(str);
        m_lab_time->setText("");
    }
    else {
        m_btn_opt->setIcon(QIcon(":/PAUSE"));
    }
    m_flg = !m_flg;
}

QString UpView::fileSizeUnit(quint64 &size)
{
    if(size/1024 == 0) {
        return "B";
    }
    else if(size/1024/1024 == 0) {
        size = size /1024;
        return "KB";
    }
    else if(size/1024/1024/1024 == 0) {
        size = size /1024/1024;
        return "M";
    }
    else {
        size = size /1024/1024/1024;
        return "G";
    }
}

QString UpView::speedUnit(double &size)
{
    if(size/1024 < 1) {
        return "B/S";
    }
    size = size/1024;
    if(size/1024 < 1) {
        return "KB/S";
    }
    size = size/1024;
    if(size/1024 < 1) {
        return "M/S";
    }
    size = size/1024;
    return "G/S";
}
QTime UpView::curTime() const
{
    return m_curTime;
}

void UpView::setCurTime(const QTime &curTime)
{
    m_curTime = curTime;
}

quint64 UpView::upBytes() const
{
    return m_upBytes;
}

void UpView::setUpBytes(const quint64 &haveDownBytes)
{
    m_upBytes = haveDownBytes;
}

quint32 UpView::dec() const
{
    return m_dec;
}

void UpView::setDec(const quint32 &dec)
{
    m_dec = dec;
}

QString UpView::fileName() const
{
    return m_fileName;
}

