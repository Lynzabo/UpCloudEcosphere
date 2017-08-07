#include "loading.h"
#include "ui_loading.h"
#include <QPainter>
#include <QMovie>
Loading::Loading(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Loading)
{
    ui->setupUi(this);
    this->widget = parent;
    //设置在子窗口关闭时销毁这个类的对象
    setAttribute(Qt::WA_DeleteOnClose);
    //初始化窗口基本数据
    initWindow();
}

Loading::~Loading()
{
    delete ui;
}

void Loading::setMsg(const QString &msg)
{
    ui->l_detail->clear();
    ui->l_detail->setText(msg.trimmed());
}

void Loading::paintEvent(QPaintEvent *e)
{

    if(!this->isHidden())
        this->resize(widget->size());
    QWidget::paintEvent(e);
    QPainter painter(this);
    painter.fillRect(rect(),QColor(219,219,219,100));
}

void Loading::initWindow()
{
    QMovie *movie = new QMovie(this);
    movie->setCacheMode(QMovie::CacheAll);
    movie->stop();
    movie->setScaledSize(ui->l_icon->size());
    ui->l_icon->setMovie(movie);
    movie->setFileName(QString(":/core/imgs/imgs/loading"));
    movie->start();
}
