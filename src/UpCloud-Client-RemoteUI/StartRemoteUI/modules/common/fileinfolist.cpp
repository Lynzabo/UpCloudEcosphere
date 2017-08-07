#include "fileinfolist.h"
#include "ui_fileinfolist.h"
#include "filedialog.h"
#include "filedirwidget.h"
#include "uihelper.h"
#include "baseiremote.h"
#include <QFileInfo>
#include <QFileInfoList>
FileInfoList::FileInfoList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileInfoList)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_ShowModal,true);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    m_filePathList.clear();
    m_srcDir.clear();
    //注册系统日志自定义格式监听器
    ClientConf cliconif;
    cliconif.getFtpRootPath(m_defaultSaveDir);
    if(m_defaultSaveDir.lastIndexOf("/") == m_defaultSaveDir.size() -1 )
    {
        m_defaultSaveDir.resize(m_defaultSaveDir.size() -1);
    }
    initWindow();
}

FileInfoList::~FileInfoList()
{
    delete ui;
}

void FileInfoList::initWindow()
{
    //广播选中1行
    connect(ui->tableWidget,&TableWidget::evt_selectedRow,this,&FileInfoList::on_selectedRow);
    //广播选中多行
    connect(ui->tableWidget,&TableWidget::evt_selectedRows,this,&FileInfoList::on_selectedRows);
    //广播双击1行
    connect(ui->tableWidget,&TableWidget::evt_doubleSelected,this,&FileInfoList::on_doubleSelected);
    ui->tableWidget->setHeaderColumnWidth(FileInfoList::FILE_NAME,  10.0/100);
    ui->tableWidget->setHeaderColumnWidth(FileInfoList::SRC_ABST,40.0/100);
    ui->tableWidget->setHeaderColumnWidth(FileInfoList::SAVE_ABST,40.0/100);
    ui->tableWidget->setHeaderColumnWidth(FileInfoList::WORK_ABST,10.0/100);
    m_menu  = new QMenu(this);
    QAction* fileAction = new QAction(tr("选择文件"),this);
    connect(fileAction,SIGNAL(triggered(bool)),this,SLOT(on_selectFileSrcAbst()));
    m_menu->addAction(fileAction);

    QAction* dirAction = new QAction(tr("selectedFileDir"),this);
    connect(dirAction,SIGNAL(triggered(bool)),this,SLOT(on_selectDirSrcAbst()));
    m_menu->addAction(dirAction);
}

void FileInfoList::loadDatas()
{
    m_saveAbst.clear();
    int rowCount = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(m_curSelectFiles.size() + rowCount);
    for(int i = 0;i < m_curSelectFiles.size(); ++i)
    {
        QString filePath = m_curSelectFiles.at(i);
        QTableWidgetItem* item1 = new QTableWidgetItem;
        QString fileName = filePath.right(filePath.size() -  filePath.lastIndexOf("/") -1);
        item1->setText(fileName);
        ui->tableWidget->setItem(i+ rowCount,TableHeaderElement::FILE_NAME,item1);

        QTableWidgetItem* item2 = new QTableWidgetItem;
        item2->setText(filePath);
        ui->tableWidget->setItem(i+ rowCount,TableHeaderElement::SRC_ABST,item2);

        QTableWidgetItem* item3 = new QTableWidgetItem;
        filePath.remove(0,m_selectWorkDir.size());
        int index = filePath.lastIndexOf("/");
        filePath.resize(index);
        item3->setText( m_defaultSaveDir + filePath);
        m_saveDirList << m_defaultSaveDir;
        ui->tableWidget->setItem(i+ rowCount,TableHeaderElement::SAVE_ABST,item3);

        QTableWidgetItem* item4 = new QTableWidgetItem;
        item4->setText(m_selectWorkDir );
        ui->tableWidget->setItem(i+ rowCount,TableHeaderElement::WORK_ABST,item4);
    }


}

void FileInfoList::updateSaveAbst()
{
    if(m_selectedRows.isEmpty()) {
        UIHelper::ShowMessageBoxError(tr("Please select a message"));
        return;
    }
    if(m_selectSaveDir.lastIndexOf("/") == m_selectSaveDir.size() -1 )
    {
        m_selectSaveDir.resize(m_selectSaveDir.size() -1);
    }
    for(int row:m_selectedRows) {
        QString saveDir = m_saveDirList.at(row);
        QTableWidgetItem* item = ui->tableWidget->item(row,TableHeaderElement::SAVE_ABST);
        QString saveAbst = item->text();
        saveAbst.replace(0,saveDir.size(),m_selectSaveDir );
        item->setText(saveAbst);
    }
}

void FileInfoList::on_selectedRow(int selectedRow)
{
    m_selectedRows.clear();
    m_selectedRows.append(selectedRow);
}

void FileInfoList::on_selectedRows(QList<int> selectedRows)
{
    m_selectedRows.clear();
    m_selectedRows.append(selectedRows);
}

void FileInfoList::on_doubleSelected(int selectedRow)
{
    m_selectedRows.clear();
    m_selectedRows.append(selectedRow);
}

void FileInfoList::on_selectFileSrcAbst()
{
    FileDialog* fileDlg = new FileDialog;
    connect(fileDlg,SIGNAL(directoryEntered(QString)),this,SLOT(on_selectWorkDir(QString)));
    connect(fileDlg,SIGNAL(filesSelected(QStringList)),this,SLOT(on_selectSrcFiles(QStringList)));
    fileDlg->show();
}

void FileInfoList::on_selectDirSrcAbst()
{
    FileDialog* dirDlg = new FileDialog;
    dirDlg->setFileMode(QFileDialog::Directory);
    connect(dirDlg,SIGNAL(directoryEntered(QString)),this,SLOT(on_selectWorkDir(QString)));
    connect(dirDlg,SIGNAL(fileSelected(QString)),this,SLOT(on_selectSrcDir(QString)));
    dirDlg->show();
}

void FileInfoList::on_selectSaveDir(const QString &dir)
{
    m_selectSaveDir  = dir;
    updateSaveAbst();
}


void FileInfoList::on_selectSrcFiles(const QStringList &files)
{
    m_curSelectFiles.clear();
    m_curSelectFiles = files;
    m_filePathList.append(files);
    loadDatas();
}

void FileInfoList::on_selectSrcDir(const QString &url)
{
    m_curSelectFiles.clear();
    m_curSelectFiles.append(url);
    m_srcDir.append(url);
    loadDatas();
}

void FileInfoList::on_selectWorkDir(const QString &dir)
{
    m_selectWorkDir = dir;
    if(m_selectWorkDir.lastIndexOf("/") == m_selectWorkDir.size() -1 )
    {
        m_selectWorkDir.resize(m_selectWorkDir.size() -1);
    }
}

void FileInfoList::on_btn_select_file_clicked()
{
//    QPoint p = ui->btn_select_file->pos();

//    p.setX(p.y() + ui->btn_select_file->height());
    m_menu->exec(QCursor::pos());
}

void FileInfoList::on_btn_del_file_clicked()
{
    if(m_selectedRows.size() < 1) {
        return;
    }
    int ok = UIHelper::ShowMessageBoxQuesion(tr("你确定要删除记录吗?"));
    if(!ok) {
        return;
    }
    for(int row = m_selectedRows.size() -1; row > -1; --row) {
        m_filePathList.removeAt(row);
        ui->tableWidget->removeRow(row);
        m_saveDirList.removeAt(row);
    }
    m_selectedRows.clear();

}

void FileInfoList::on_btn_set_save_path_clicked()
{
    if(m_selectedRows.isEmpty()) {
        UIHelper::ShowMessageBoxError(tr("Please select a message"));
        return;
    }
    FileDirWidget* fileDir = new FileDirWidget;
    fileDir->setDefaultDir(m_defaultSaveDir);
    connect(fileDir,SIGNAL(evt_selectDir(QString)),this,SLOT(on_selectSaveDir(QString)));
            fileDir->show();
}

QString FileInfoList::defaultSaveDir() const
{
    return m_defaultSaveDir;
}

void FileInfoList::setDefaultSaveDir(const QString &defaultSaveDir)
{
    m_defaultSaveDir = defaultSaveDir;
}

void FileInfoList::on_btn_save_clicked()
{
    m_srcAbst.clear();
    m_saveAbst.clear();
   for(int row = 0;row < ui->tableWidget->rowCount(); ++row) {
       QTableWidgetItem* item1 = ui->tableWidget->item(row,TableHeaderElement::SRC_ABST);
       QTableWidgetItem* item2 = ui->tableWidget->item(row,TableHeaderElement::SAVE_ABST);
       QString srcStr = item1->text();
       if(m_srcDir.contains(srcStr)) {
           bool flg  = loadDirFiles(srcStr,srcStr,item2->text());
           if(!flg) {
               UIHelper::ShowMessageBoxError(tr("选中的文件夹包含已经选择的单文件"));
               return;
           }
       }
       else {
           m_srcAbst.append(srcStr);
           m_saveAbst.append(item2->text());
       }
   }
   emit evt_selectedFileInfoList(m_srcAbst,m_saveAbst);
   this->hide();
}

void FileInfoList::on_btn_cancel_clicked()
{
    this->deleteLater();
}

bool FileInfoList::loadDirFiles(const QString &path, const QString &srcPath, const QString &SavePath)
{
    QDir dir(path);
    //不用检测 也可以
    if(!dir.exists()) {
        return false;
    }
    dir.setFilter(QDir::Dirs | QDir::Files);
    dir.setSorting(QDir::DirsFirst);
    QFileInfoList fileInfoList = dir.entryInfoList();

    for(int i = 0 ;i < fileInfoList.size(); ++i) {
        QFileInfo info= fileInfoList.at(i);

        bool isDir = info.isDir();
        if(isDir) {
            if(info.fileName() == "." || info.fileName() == "..") {
                continue;
            }
            bool flg = loadDirFiles(info.path() + "/" + info.fileName(),srcPath,SavePath);
            if(!flg) {
                return false;
            }
            continue;
        }
        else {
            QString srcAbst = info.path() + "/" + info.fileName();
            if(m_srcAbst.contains(srcAbst)) {
                UIHelper::ShowMessageBoxError(tr("选中的文件夹包含已经选择的单文件"));
                return false;
            }
            m_srcAbst.append(srcAbst);
            QString saveAbst = info.path();
            saveAbst.replace(0,srcPath.size(),SavePath);
            m_saveAbst.append(saveAbst);
        }
    }
    return true;
}
void FileInfoList::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void FileInfoList::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void FileInfoList::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void FileInfoList::on_btn_menu_cancel_clicked()
{
    this->deleteLater();
}
