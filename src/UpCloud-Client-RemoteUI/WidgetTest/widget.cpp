#include "widget.h"
#include "ui_widget.h"
#include <stdio.h>
#include "ftp/ftpmeta.h"
#include <QMessageBox>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    fileDlg = new FFileDialog;
    connect(fileDlg,SIGNAL(filesSelected(QStringList)),this,SLOT(on_selectedSrcAbst(QStringList)));
    fileDlg->show();

}

void Widget::setThreadConnectFtp()
{

    connect(downthread,SIGNAL(startS()),this,SLOT(on_downStart()));
    connect(downthread,SIGNAL(subFileEnd(const QString ,const QString ,const QString )),
            this,SLOT(on_downSubFileEnd(const QString ,const QString ,const QString )));
    connect(downthread,SIGNAL(end(const QString )),this,SLOT(on_downEnd(const QString )));
    connect(downthread,SIGNAL(error(const QString ,const QString ,const QString )),
            this,SLOT(on_downError(const QString ,const QString ,const QString )));
    connect(downthread,SIGNAL(process( QString ,quint64 , quint64 )),
            this,SLOT(on_downProcess(QString,quint64,quint64)));

    connect(upthread,SIGNAL(startS()),this,SLOT(on_upStart()));
    connect(upthread,SIGNAL(subFileEnd(const QString ,const QString ,const QString )),
            this,SLOT(on_upSubFileEnd(const QString ,const QString ,const QString )));
    connect(upthread,SIGNAL(end(const QString )),this,SLOT(on_upEnd(const QString )));
    connect(upthread,SIGNAL(error(const QString ,const QString ,const QString )),
            this,SLOT(on_upError(const QString ,const QString ,const QString )));
    connect(upthread,SIGNAL(process( QString ,quint64 , quint64 )),
            this,SLOT(on_upProcess(QString,quint64,quint64)));



}

Widget::~Widget()
{
    m_downFileList.clear();
    qDeleteAll(m_downViewList);
    m_downViewList.clear();
    m_downFileView.clear();
    delete m_downVlayout;
    delete m_downHlayout;
    delete m_ftpPool;
    m_upFileList.clear();
    qDeleteAll(m_upViewList);
    m_upViewList.clear();
    m_upFileView.clear();
    delete m_upVlayout;
    delete m_upHlayout;
    delete m_ftpUpPool;
    delete fileDlg;
    delete ui;
}

void Widget::initWidget()
{
    foreach(const QString &str,m_downNameList) {
        DownView* view = new DownView(ui->download);
        view->initView();
        int index = m_downNameList.indexOf(str);
        view->setFileName(m_downFileList.at(index));
        m_downFileView.insert(str,view);
        connect(view,SIGNAL(evt_end(DownView*)),this,SLOT(on_downDelItem(DownView*)));
        m_downViewList.push_back(view);
    }

    foreach(const QString &str,m_upNameList) {
        UpView* view = new UpView(ui->upload);
        view->initView();
        int index = m_upNameList.indexOf(str);
        view->setFileName(m_upFileList.at(index));
        m_upFileView.insert(str,view);
        connect(view,SIGNAL(evt_end(UpView*)),this,SLOT(on_upDelItem(UpView*)));
        m_upViewList.push_back(view);
    }

}

void Widget::showDownViewList()
{

    if(m_downVlayout) {
        return;
    }
    m_downVlayout = new QVBoxLayout;
    m_downHlayout = new QHBoxLayout;
    m_downHlayout->addStretch(300);
    m_downHlayout->addWidget(ui->m_down_start);
    m_downHlayout->addStretch(10);
    m_downHlayout->addWidget(ui->m_down_end);
    m_downVlayout->addLayout(m_downHlayout);
    if(!m_downViewList.isEmpty()) {
        for(QList<DownView*>::iterator item = m_downViewList.begin(); item != m_downViewList.end(); ++item) {
            (*item)->show();
            m_downVlayout->addWidget(*item);
            (*item)->setMinimumHeight(55);
        }
        ui->tabWidget->setTabText(1,QString(tr("正在下载(%1)")).arg(QString::number(m_downViewList.size())));
    }
    else {
        ui->tabWidget->setTabText(1,QString(tr("正在下载")));
    }
    m_downVlayout->addStretch(50);
    ui->download->setLayout(m_downVlayout);
}

void Widget::showUpViewList()
{
    if(m_upVlayout) {
        return;
    }
    m_upVlayout = new QVBoxLayout;
    m_upHlayout = new QHBoxLayout;
    m_upHlayout->addStretch(300);
    m_upHlayout->addWidget(ui->m_up_start);
    m_upHlayout->addStretch(10);
    m_upHlayout->addWidget(ui->m_up_end);
    m_upVlayout->addLayout(m_upHlayout);
    if(!m_upViewList.isEmpty()) {
        for(QList<UpView*>::iterator item = m_upViewList.begin(); item != m_upViewList.end(); ++item) {
            (*item)->show();
            m_upVlayout->addWidget(*item);
            (*item)->setMinimumHeight(55);
        }
        ui->tabWidget->setTabText(0,QString(tr("正在上传(%1)")).arg(QString::number(m_upViewList.size())));
    }
    else {
        ui->tabWidget->setTabText(0,QString(tr("正在上传")));
    }
    m_upVlayout->addStretch(50);
    ui->upload->setLayout(m_upVlayout);
}

void Widget::initWindow()
{
    FtpMeta::Builder *builder = new FtpMeta::Builder;
    FtpMeta *meta = (FtpMeta *)builder->setHostname(QString("10.0.0.2"))
            ->setPort(21)
            ->setUsername(QString("ftpdemo"))
            ->setPassword(QString("123456"))->build();
    m_downHlayout = 0;
    m_downVlayout = 0;

    m_upHlayout = 0;
    m_upVlayout = 0;

    m_ftpPool = new FTPClientPool(meta);
    m_downFileView.clear();
    downthread = new DownThread;
    m_downGroupFile.clear();
    m_downGroupFile.insert("ftp://10.0.0.2:21/001162c91d554e23ad65dfc3a8cb8129.jpg","E:/001162c91d554e23ad65dfc3a8cb8129.jpg");
    m_downGroupFile.insert("ftp://10.0.0.2:21/00123f56e0e747b6a8142eadcbd28b96.xml","E:/00123f56e0e747b6a8142eadcbd28b96.xml");
    m_downGroupFile.insert("ftp://10.0.0.2:21/00174c92919b47a3ae13263eddba7d73.mp4","E:/00174c92919b47a3ae13263eddba7d73.mp4");
    //源文件路径列表
    m_downNameList = m_downGroupFile.keys();
    setDownFileNameList(m_downGroupFile.values());
    //给线程传递参数
    downthread->setFtpPool(m_ftpPool);
    downthread->setFiles(m_downGroupFile);

    m_upFileView.clear();
    upthread = new UpThread;
    m_upGroupFile.clear();
    foreach(const QString &url,srcAbstList) {
        QUrl dir(url);
        QString fileName = dir.fileName();
        QString saveAbst = "ftp://10.0.0.2:21/" + fileName;
        m_upGroupFile.insert(url,saveAbst);
    }
//    m_upGroupFile.insert("E:/UpCloudEcosphere.zip","ftp://10.0.0.2:21/UpCloudEcosphere.zip");
//    m_upGroupFile.insert("E:/ProjectProfessional.exe","ftp://10.0.0.2:21/ProjectProfessional.exe");
    //源文件路径列表
    m_upNameList = m_upGroupFile.keys();
    setUpFileNameList(m_upGroupFile.values());
    //给线程传递参数
    m_ftpUpPool= new FTPClientPool(meta);
    upthread->setFtpPool(m_ftpUpPool);
    upthread->setFiles(m_upGroupFile);
    //与线程连接信号槽
    this->setThreadConnectFtp();
    this->initWidget();
    this->showDownViewList();
    this->showUpViewList();
}

void Widget::setDownFileNameList(const QStringList &list)
{
    //新文件路径列表
    m_downFilePath = list;
    foreach(const QString& str,list) {
        QString name = str.mid(str.lastIndexOf("/") + 1);
        //新文件
        m_downFileList.push_back(name);
    }
}

void Widget::setUpFileNameList(const QStringList &list)
{
    //新文件路径列表
    m_upFilePath = list;
    foreach(const QString& str,list) {
        QString name = str.mid(str.lastIndexOf("/") + 1);
        //新文件
        m_upFileList.push_back(name);
    }
}

void Widget::on_downStart()
{

}

void Widget::on_downSubFileEnd(const QString &taskID, const QString &fileUrl, const QString &destAbst)
{
    DownView* view = m_downFileView.value(fileUrl);
    view->endDown();
}

void Widget::on_downEnd(const QString &taskID)
{
    qDebug() << "my end" ;
}

void Widget::on_downProcess(const QString &fileUrl, const quint64 &haveDoneBytes, const quint64 &totalBytes)
{
    DownView* view = m_downFileView.value(fileUrl);
    //更新下载信息
    view->updateInfo(haveDoneBytes,totalBytes);
}

void Widget::on_downError(const QString &taskID, const QString &src, const QString &errMsg)
{

}

void Widget::on_downDelItem(DownView* item)
{
    QMessageBox* msg = new QMessageBox(QMessageBox::NoIcon,QObject::tr("删除"),QObject::tr("删除文件吗?"),QMessageBox::Yes | QMessageBox::No,this);

    int index;
    if(msg->exec() == QMessageBox::Yes)
    {
        index = m_downViewList.indexOf(item);
        m_downFileView.remove(item->fileName());
        m_downViewList.removeOne(item);
        QString path =  m_downFilePath.at(index);
        m_downFilePath.removeAt(index);
        index = path.lastIndexOf("/");
        qDebug() << path;
        path = path.left(index);
        QDir dir(path);
        dir.remove(item->fileName());
        path =  item->fileName();
    }
    delete m_downHlayout;
    delete m_downVlayout;
    m_downHlayout = 0;
    m_downVlayout = 0;
    this->showDownViewList();
}

void Widget::on_selectedSrcAbst(const QStringList &src)
{
    srcAbstList = src;
    initWindow();

}

void Widget::on_upStart()
{

}

void Widget::on_upSubFileEnd(const QString &taskID, const QString &fileUrl, const QString &destAbst)
{
    UpView* view = m_upFileView.value(fileUrl);
    view->endDown();
}

void Widget::on_upEnd(const QString &taskID)
{

}

void Widget::on_upProcess(const QString &fileUrl, const quint64 &haveDoneBytes, const quint64 &totalBytes)
{
    UpView* view = m_upFileView.value(fileUrl);
    //更新下载信息
    view->updateInfo(haveDoneBytes,totalBytes);
}

void Widget::on_upError(const QString &taskID, const QString &src, const QString &errMsg)
{

}

QStringList Widget::fileList() const
{
    return m_downFileList;
}

void Widget::setFileList(const QStringList &fileList)
{
    m_downFileList = fileList;
}

void Widget::addFileDown(const QString &fileUrl)
{
    m_downFileList.append(fileUrl);
    DownView* view = new DownView(ui->download);
    view->initView();
    view->setFileName(fileUrl);
    m_downFileView.insert(fileUrl,view);
    connect(view,SIGNAL(evt_end()),this,SLOT(on_downDelItem()));
    m_downViewList.push_back(view);
    delete m_downHlayout;
    delete m_downVlayout;
    m_downHlayout = 0;
    m_downVlayout = 0;
    this->showDownViewList();
}



void Widget::on_down()
{

    downthread->start();
}

void Widget::on_upDelItem(UpView *item)
{
    QMessageBox* msg = new QMessageBox(QMessageBox::NoIcon,QObject::tr("删除"),QObject::tr("删除文件吗?"),QMessageBox::Yes | QMessageBox::No,this);

    int index;
    if(msg->exec() == QMessageBox::Yes)
    {
        index = m_upViewList.indexOf(item);
        m_upFileView.remove(item->fileName());
        m_upViewList.removeOne(item);
        QString path =  m_upFilePath.at(index);
        m_upFilePath.removeAt(index);
        index = path.lastIndexOf("/");
        qDebug() << path;
        path = path.left(index);
        QDir dir(path);
        dir.remove(item->fileName());
        path =  item->fileName();
    }
    delete m_upHlayout;
    delete m_upVlayout;
    m_upHlayout = 0;
    m_upVlayout = 0;
    this->showUpViewList();
}

void Widget::on_up()
{
    upthread->start();
}



void Widget::on_m_down_start_clicked()
{
    QTimer::singleShot(10,this,SLOT(on_down()));
}

void Widget::on_m_down_end_clicked()
{
    qDeleteAll(m_downViewList);
    m_downViewList.clear();
    delete m_downHlayout;
    delete m_downVlayout;
    this->showDownViewList();
}

void Widget::on_m_up_start_clicked()
{
    QTimer::singleShot(10,this,SLOT(on_up()));
}

void Widget::on_m_up_end_clicked()
{
    qDeleteAll(m_upViewList);
    m_upViewList.clear();
    delete m_upHlayout;
    delete m_upVlayout;
    this->showUpViewList();
}
