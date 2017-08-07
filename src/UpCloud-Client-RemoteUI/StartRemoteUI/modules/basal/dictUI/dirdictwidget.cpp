#include "dirdictwidget.h"
#include "ui_dirdictwidget.h"
#include "modules/common/uihelper.h"
DirDictWidget::DirDictWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DirDictWidget)
{
    ui->setupUi(this);

    splitter = new QSplitter(Qt::Horizontal, this);
    splitter->setHandleWidth(1);
    initWindow();
    dictMinW = width()*7/10;
    selectDict->resize(dictMinW, height());
    treeMaxW = width() - selectDict->width();
    dictTree->resize(treeMaxW, height());
    connect(splitter, SIGNAL(splitterMoved(int,int)), this, SLOT(slotSplitterMoved(int,int)));

    leftIcon = QIcon(":/left.png");
    rightIcon = QIcon(":/right.png");

    pushButton = new QPushButton("sdasd",this);
    pushButton->setFocusPolicy(Qt::NoFocus);
    pushButton->hide();
    pushButton->setFixedSize(13, 42);
    pushButton->setIconSize(pushButton->size());
    pushButton->setIcon(rightIcon);
    pushButton->setMouseTracking(true);
    connect(pushButton,SIGNAL(clicked()),this,SLOT(slotClickedBtn()));

    selectDict->setMouseTracking(true);
    dictTree->setMouseTracking(true);
    selectDict->installEventFilter(this);
    dictTree->installEventFilter(this);
}

DirDictWidget::~DirDictWidget()
{
    delete ui;
}

void DirDictWidget::initWindow()
{
    dictTree = new DictTree(splitter);
    dictTree->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    selectDict = new SelectDictWidget(splitter);
    connect(dictTree,SIGNAL(evt_itemClicked(QString,QString)),selectDict,SLOT(on_itemClicked(QString,QString)));
    connect(selectDict,SIGNAL(evt_reload()),dictTree,SLOT(on_reload()));
    connect(selectDict,SIGNAL(evt_delDicts(QList<QString>)),dictTree,SLOT(on_delNode(QList<QString>)));
    connect(selectDict,SIGNAL(evt_addDict(CsDict)),dictTree,SLOT(on_addNode(CsDict)));
}



void DirDictWidget::resizeEvent(QResizeEvent *event)
{
    splitter->setGeometry(0, 0, width(), height());
    //    move((QApplication::desktop()->width() - width())/2,  (QApplication::desktop()->height() - height())/2);
    QWidget::resizeEvent(event);
}

bool DirDictWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseMove) {
        QMouseEvent *mouseMove = static_cast<QMouseEvent*>(event);
        QRect rect = pushButton->frameGeometry();
        rect.setWidth(rect.width() + 20);
        QPoint pos = mouseMove->pos();
        pos.setX(pos.x() + dictTree->width());
        pos.setY(pos.y());
        if (rect.contains(pos)) {
            pushButton->show();
        }
        else {
            pushButton->hide();
        }
    }
    return QWidget::eventFilter(obj, event);
}

void DirDictWidget::showEvent(QShowEvent *event)
{

    pushButton->move(dictTree->width()+2, (height() - pushButton->height())/2);
}

void DirDictWidget::setBtnPos()
{
    pushButton->move(dictTree->width() + 2, (height() - pushButton->height())/2);
}

void DirDictWidget::setBtnIcon()
{
    if (dictTree->width() != 0) {
        pushButton->setIcon(rightIcon);
    }
    else {
        pushButton->setIcon(leftIcon);
    }
}

void DirDictWidget::slotClickedBtn()
{
    QList <int> sizeList;
    sizeList.clear();
    if (dictTree->width() != 0) {
        sizeList.append(0);
        sizeList.append(this->width());
    }
    else {
        sizeList.append(treeMaxW);
        sizeList.append(dictMinW);
    }
    splitter->setSizes(sizeList);

    setBtnIcon();
    setBtnPos();
    pushButton->hide();
}

void DirDictWidget::slotSplitterMoved(int pos, int index)
{
    Q_UNUSED(pos)
    Q_UNUSED(index)
    setBtnIcon();
    setBtnPos();
}



void DirDictWidget::mouseMoveEvent(QMouseEvent *event)
{

    QWidget::mouseMoveEvent(event);
}


void DirDictWidget::loadSelectWidget(const QString &uuid)
{

}





