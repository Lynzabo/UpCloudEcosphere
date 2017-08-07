#include "createtaskwidget.h"
#include "ui_createtaskwidget.h"
#include "../FrontBusinessIRemoteUI/BasalOperaIRemoteUI/basaloperairemoteui.h"
#include "uihelper.h"
#include "../StartRemoteUI/modules/ddmi/unstructUI/dirunstructwidget.h"
#include "filedirwidget.h"
using namespace RemoteUIEnvironment::CallbackStatus;
CreateTaskWidget::CreateTaskWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateTaskWidget)
{
    ui->setupUi(this);
    addrFlag = false;
    fileFlag = false;
    QDateTime time = QDateTime::currentDateTime();
    ui->dte_exec_time->setDateTime(time);
    ui->dte_parse_time->setDateTime(time);
    ui->dte_send_time->setDateTime(time);
    treeWidget = 0;
    fileDlg = 0;

    ClientConf cliconif;
    cliconif.getFtpRootPath(m_defaultSaveDir);
    if(m_defaultSaveDir.lastIndexOf("/") == m_defaultSaveDir.size() -1 )
    {
        m_defaultSaveDir.resize(m_defaultSaveDir.size() -1);
    }

    initWindow();
    ui->cb_taskState->setCurrentIndex(1);
}

void CreateTaskWidget::setAddTaskInfo(CsRUnstructTask *task,
                                      QList<CsRUnstructSendAddr>* addrInfoList,
                                      QList<CsRUnstructSendFiles>* fileInfoList,
                                      QList<CsRUnstructSendStatus>* statusInfoList)
{
    m_unstruct_task = task;
    unstruct_addrInfoList = addrInfoList;
    unstruct_fileInfoList = fileInfoList;
    unstruct_statusInfoList = statusInfoList;
    m_operaType = UNSTRUCT_TYPE;
    ui->dte_exec_time->hide();
    ui->dte_parse_time->hide();
    ui->lab_exec_time->hide();
    ui->lab_parse_time->hide();
}

void CreateTaskWidget::setAddTaskInfo(CsRStructTask *task, QList<CsRStructSendAddr> *addrInfoList, QList<CsRStructSendFiles> *fileInfoList, QList<CsRStructSendStatus> *statusInfoList)
{
    m_struct_task = task;
    struct_addrInfoList = addrInfoList;
    struct_fileInfoList = fileInfoList;
    struct_statusInfoList = statusInfoList;
    m_operaType = STRUCT_TYPE;
    ui->lab_exec_time->hide();
    ui->dte_exec_time->hide();
}

CreateTaskWidget::~CreateTaskWidget()
{
    delete ui;
}

void CreateTaskWidget::showSelectedFiles()
{
    m_saveAbst.clear();
    int rowCount = ui->tw_files_content->rowCount();
    ui->tw_files_content->setRowCount(m_curSelectFiles.size() + rowCount);
    for(int i = 0; i< m_curSelectFiles.size(); ++i) {
        QString filePath = m_curSelectFiles.at(i);
        QTableWidgetItem* item1 = new QTableWidgetItem;
        QString fileName = filePath.right(filePath.size() -  filePath.lastIndexOf("/") -1);
        item1->setText(fileName);
        ui->tw_files_content->setItem(i+ rowCount,FilesTableHeaderElement::FILE_NAME,item1);

        QTableWidgetItem* item2 = new QTableWidgetItem;
        item2->setText(filePath);
        ui->tw_files_content->setItem(i+ rowCount,FilesTableHeaderElement::SRC_ABST,item2);

        QTableWidgetItem* item3 = new QTableWidgetItem;
        filePath.remove(0,m_selectWorkDir.size());
        int index = filePath.lastIndexOf("/");
        filePath.resize(index);
        item3->setText( m_defaultSaveDir + filePath);
        m_saveDirList << m_defaultSaveDir;
        ui->tw_files_content->setItem(i+ rowCount,FilesTableHeaderElement::SAVE_ABST,item3);

        QTableWidgetItem* item4 = new QTableWidgetItem;
        item4->setText(m_selectWorkDir );
        ui->tw_files_content->setItem(i+ rowCount,FilesTableHeaderElement::WORK_ABST,item4);


    }
}

bool CreateTaskWidget::setFileList()
{
    m_srcAbst.clear();
    m_saveAbst.clear();
    for(int row = 0;row < ui->tw_files_content->rowCount(); ++row) {
        QTableWidgetItem* item1 = ui->tw_files_content->item(row,FilesTableHeaderElement::SRC_ABST);
        QTableWidgetItem* item2 = ui->tw_files_content->item(row,FilesTableHeaderElement::SAVE_ABST);
        QString srcStr = item1->text();
        if(dirIndexList.contains(row)) {
            bool flg = loadDirFiles(srcStr,srcStr,item2->text());
            if(!flg) {
                return false;
            }
        }
        else {
            m_srcAbst.append(srcStr);
            m_saveAbst.append(item2->text());
        }
    }
    if(m_operaType == UNSTRUCT_TYPE) {
        (*unstruct_fileInfoList).clear();
        for(int i = 0; i< m_srcAbst.size(); ++i) {
            CsRUnstructSendFiles file;
            file.setFileName(m_srcAbst.at(i));
            file.setSaveAbst(m_saveAbst.at(i));
            (*unstruct_fileInfoList).append(file);
        }
    }
    else if(m_operaType == STRUCT_TYPE) {
        (*struct_fileInfoList).clear();
        for(int i = 0; i< m_srcAbst.size(); ++i) {
            CsRStructSendFiles file;
            file.setFileName(m_srcAbst.at(i));
            file.setSaveAbst(m_saveAbst.at(i));
            (*struct_fileInfoList).append(file);
        }
    }
    else if(m_operaType == SCHEDULE_TYPE) {

    }
    return true;
}

void CreateTaskWidget::on_selectedNodes()
{
    if(m_operaType == UNSTRUCT_TYPE ) {
        (*unstruct_addrInfoList).clear();
        if(selectedClientUuids.isEmpty() ) {
            addrFlag = false;
        }
        else {
            for(int i = 0; i < selectedClientUuids.size(); ++i) {
                CsRUnstructSendAddr addr;
                addr.setClientUuid(selectedClientUuids.at(i));
                addr.setGroupDesc(nodesDescription.at(i));
                (*unstruct_addrInfoList).append(addr);
            }
            ui->tw_nodes_content->setRowCount(selectedClientUuids.size());
            for(int i = 0; i< selectedClientUuids.size(); ++i) {
                QTableWidgetItem* item = new QTableWidgetItem;
                item->setText(selectedClientUuids.at(i));
                ui->tw_nodes_content->setItem(i,NodesTableHeaderElement::NODE_NAME,item);

                QTableWidgetItem* item1 = new QTableWidgetItem;
                item1->setText(nodesDescription.at(i));
                ui->tw_nodes_content->setItem(i,NodesTableHeaderElement::GROUP_DESCRIPTION,item1);

            }

            addrFlag = true;
        }
    }
    else if(m_operaType == STRUCT_TYPE ) {
        (*struct_addrInfoList).clear();
        if(selectedClientUuids.isEmpty() ) {
            addrFlag = false;
        }
        else {
            for(int i = 0; i < selectedClientUuids.size(); ++i) {
                CsRStructSendAddr addr;
                addr.setClientUuid(selectedClientUuids.at(i));
                addr.setGroupDesc(nodesDescription.at(i));
                (*struct_addrInfoList).append(addr);
            }
            if(!ui->tw_nodes_content->rowCount()) {
                ui->tw_nodes_content->setRowCount(selectedClientUuids.size());
                for(int i = 0; i< selectedClientUuids.size(); ++i) {
                    QTableWidgetItem* item = new QTableWidgetItem;
                    item->setText(selectedClientUuids.at(i));
                    ui->tw_nodes_content->setItem(i,NodesTableHeaderElement::NODE_NAME,item);

                    QTableWidgetItem* item1 = new QTableWidgetItem;
                    item1->setText(nodesDescription.at(i));
                    ui->tw_nodes_content->setItem(i,NodesTableHeaderElement::GROUP_DESCRIPTION,item1);

                }
            }
            addrFlag = true;
        }
    }
}


void CreateTaskWidget::initWindow()
{
    //广播选中1行
    connect(ui->tw_nodes_content,&TableWidget::evt_selectedRow,this,&CreateTaskWidget::on_nodesSelectedRow);
    //广播选中多行
    connect(ui->tw_nodes_content,&TableWidget::evt_selectedRows,this,&CreateTaskWidget::on_nodesSelectedRows);
    //广播双击1行
    connect(ui->tw_nodes_content,&TableWidget::evt_doubleSelected,this,&CreateTaskWidget::on_nodesDoubleSelected);
    ui->tw_nodes_content->setHeaderColumnWidth(NodesTableHeaderElement::NODE_NAME,  50.0/100);
    ui->tw_nodes_content->setHeaderColumnWidth(NodesTableHeaderElement::GROUP_DESCRIPTION,50.0/100);


    //广播选中1行
    connect(ui->tw_files_content,&TableWidget::evt_selectedRow,this,&CreateTaskWidget::on_filesSelectedRow);
    //广播选中多行
    connect(ui->tw_files_content,&TableWidget::evt_selectedRows,this,&CreateTaskWidget::on_filesSelectedRows);
    //广播双击1行
    connect(ui->tw_files_content,&TableWidget::evt_doubleSelected,this,&CreateTaskWidget::on_filesDoubleSelected);
    ui->tw_files_content->setHeaderColumnWidth(FilesTableHeaderElement::FILE_NAME,10.0/100);
    ui->tw_files_content->setHeaderColumnWidth(FilesTableHeaderElement::SRC_ABST,40.0/100);
    ui->tw_files_content->setHeaderColumnWidth(FilesTableHeaderElement::SAVE_ABST,40.0/100);
    ui->tw_files_content->setHeaderColumnWidth(FilesTableHeaderElement::WORK_ABST,10.0/100);

    m_menu  = new QMenu(this);
    QAction* fileAction = new QAction(tr("选择文件"),this);
    connect(fileAction,SIGNAL(triggered(bool)),this,SLOT(on_selectFileSrcAbst()));
    m_menu->addAction(fileAction);

    QAction* dirAction = new QAction(tr("setFileDir"),this);
    connect(dirAction,SIGNAL(triggered(bool)),this,SLOT(on_selectDirSrcAbst()));
    m_menu->addAction(dirAction);

    loadComboBox();
}

bool CreateTaskWidget::taskInfoIsEmply()
{

    QString taskName = ui->l_name->text().trimmed();
    if(taskName.isEmpty()) {
        return true;
    }
    QString taskDescription = ui->te_description->toPlainText().trimmed();
    if(taskDescription.isEmpty()) {
        return true;
    }
    quint8 taskState = (quint8)ui->cb_taskState->currentValue().toInt();
    quint16 taskStrategy = (quint16)ui->cb_strategy->currentValue().toInt();
    QString sendTime = ui->dte_send_time->text().trimmed();
    if(m_operaType == UNSTRUCT_TYPE) {
        m_unstruct_task->setDescription(taskDescription);
        m_unstruct_task->setTaskName(taskName);
        m_unstruct_task->setState(taskState);
        m_unstruct_task->setStrategy(taskStrategy);
        m_unstruct_task->setSendTime(sendTime);
    }
    else if(m_operaType == STRUCT_TYPE) {
        QString execTime = ui->dte_exec_time->text().trimmed();
        m_struct_task->setDescription(taskDescription);
        m_struct_task->setTaskName(taskName);
        m_struct_task->setState(taskState);
        m_struct_task->setStrategy(taskStrategy);
        m_struct_task->setSendTime(sendTime);
        m_struct_task->setExecTime(execTime);
    }
    return false;
}

void CreateTaskWidget::loadDatas()
{
    infoList.clear();
    for(int i = 0;i < selectedClientUuids.size(); ++i) {
        foreach(const QString &fileName,m_srcAbst) {
            CreateTaskInfo info;
            info.setFileName(fileName);
            //暂时为写死 是可用
            info.setFileState(1);
            info.setGroupDescription(nodesDescription.at(i));
            info.setClientUuid(selectedClientUuids.at(i));
            infoList.append(info);
        }
    }
}

void CreateTaskWidget::loadComboBox()
{
    QStringList text;
    text << tr("废弃") << tr("可用") ;
    QStringList value;
    value << tr("0") << tr("1");
    ui->cb_taskState->setShowInfo(text,value);


    text.clear();
    text << tr("默认策略");
    value.clear();
    value << tr("1");
    ui->cb_strategy->setShowInfo(text,value);
}

void CreateTaskWidget::setUnstructParams()
{

    foreach(const CreateTaskInfo& info,infoList) {
        CsRUnstructSendStatus status;
        status.setClientUuid(info.getClientUuid());
        status.setSendFileUuid(info.getFileName());
        status.setState(info.getFileState());
        (*unstruct_statusInfoList).append(status);
    }
}

void CreateTaskWidget::setStructParams()
{
    foreach(const CreateTaskInfo& info,infoList) {
        CsRStructSendStatus status;
        status.setClientUuid(info.getClientUuid());
        status.setSendFileUuid(info.getFileName());
        status.setState(info.getFileState());
        (*struct_statusInfoList).append(status);
    }
}

void CreateTaskWidget::updateSaveAbst()
{
    if(filesSelectRows.isEmpty()) {
        UIHelper::ShowMessageBoxError(tr("Please select a message"));
        return;
    }
    if(m_selectSaveDir.lastIndexOf("/") == m_selectSaveDir.size() -1 )
    {
        m_selectSaveDir.resize(m_selectSaveDir.size() -1);
    }
    for(int row:filesSelectRows) {
        QString saveDir = m_saveDirList.at(row);
        QTableWidgetItem* item = ui->tw_files_content->item(row,FilesTableHeaderElement::SAVE_ABST);
        QString saveAbst = item->text();
        saveAbst.replace(0,saveDir.size(),m_selectSaveDir );
        item->setText(saveAbst);
    }
}


void CreateTaskWidget::on_nodesSelectedRow(int selectedRow)
{
    nodesSelectRows.clear();
    nodesSelectRows.append(selectedRow);
}

void CreateTaskWidget::on_nodesSelectedRows(QList<int> selectedRows)
{
    nodesSelectRows.clear();
    nodesSelectRows.append(selectedRows);
}

void CreateTaskWidget::on_nodesDoubleSelected(int selectedRow)
{
    nodesSelectRows.clear();
    nodesSelectRows.append(selectedRow);
}

void CreateTaskWidget::on_filesSelectedRow(int selectedRow)
{
    filesSelectRows.clear();
    filesSelectRows.append(selectedRow);
}

void CreateTaskWidget::on_filesSelectedRows(QList<int> selectedRows)
{
    filesSelectRows.clear();
    filesSelectRows.append(selectedRows);
}

void CreateTaskWidget::on_filesDoubleSelected(int selectedRow)
{
    filesSelectRows.clear();
    filesSelectRows.append(selectedRow);
}





void CreateTaskWidget::on_btn_save_clicked()
{
    if(!addrFlag) {
        UIHelper::ShowMessageBoxError(tr("请添加节点服务器"));
        return;
    }
    if(!fileFlag) {
        UIHelper::ShowMessageBoxError(tr("请先添加文件列表"));
        return;
    }
    if(taskInfoIsEmply()) {
        UIHelper::ShowMessageBoxError(tr("请填写完整的任务信息"));
        return;
    }
    bool flg = setFileList();
    if(!flg) {
        return;
    }
    loadDatas();
    if(m_operaType == UNSTRUCT_TYPE) {

        setUnstructParams();
    }
    else if(m_operaType == STRUCT_TYPE) {
        setStructParams();
    }
    else {

    }
    emit evt_save();
    this->deleteLater();
}

void CreateTaskWidget::on_btn_quit_clicked()
{
    this->deleteLater();
}

void CreateTaskWidget::on_btn_nodes_add_clicked()
{
    treeWidget = new GroupTreeWidget;
    treeWidget->setParamsForClientUuid(&selectedClientUuids,&nodesDescription);
    connect(treeWidget,SIGNAL(evt_ok()),this,SLOT(on_selectedNodes()));
    treeWidget->show();
}

void CreateTaskWidget::on_btn_nodes_del_clicked()
{
    if(nodesSelectRows.size() < 1) {
        return;
    }
    int ok = UIHelper::ShowMessageBoxQuesion(tr("你确定要删除记录吗?"));
    if(!ok) {
        return;
    }
    //删除集合要逆向
    for(int i = nodesSelectRows.size() -1; i  >= 0; --i) {
        int row = nodesSelectRows.at(i);
        ui->tw_nodes_content->removeRow(row);
        if(m_operaType == UNSTRUCT_TYPE) {
            (*unstruct_addrInfoList).removeAt(row);
        }
        else if(m_operaType== STRUCT_TYPE)  {
            (*struct_addrInfoList).removeAt(row);
        }
        else if(m_operaType == SCHEDULE_TYPE) {

        }
    }
    if(ui->tw_nodes_content->rowCount() < 1) {
        addrFlag = false;
    }
}

void CreateTaskWidget::on_btn_files_add_clicked()
{
    m_menu->exec(QCursor::pos());
}

void CreateTaskWidget::on_selectFileSrcAbst()
{
    FileDialog* fileDlg = new FileDialog;
    connect(fileDlg,SIGNAL(directoryEntered(QString)),this,SLOT(on_selectWorkDir(QString)));
    connect(fileDlg,SIGNAL(filesSelected(QStringList)),this,SLOT(on_selectSrcFiles(QStringList)));
    fileDlg->show();
}

void CreateTaskWidget::on_selectDirSrcAbst()
{
    FileDialog* dirDlg = new FileDialog;
    dirDlg->setFileMode(QFileDialog::Directory);
    connect(dirDlg,SIGNAL(directoryEntered(QString)),this,SLOT(on_selectWorkDir(QString)));
    connect(dirDlg,SIGNAL(fileSelected(QString)),this,SLOT(on_selectSrcDir(QString)));
    dirDlg->show();
}

void CreateTaskWidget::on_selectSaveDir(const QString &dir)
{
    m_selectSaveDir  = dir;
    updateSaveAbst();
}

void CreateTaskWidget::on_selectSrcFiles(const QStringList &files)
{
    m_curSelectFiles.clear();
    m_curSelectFiles = files;
    if(files.size() > 0) {
        fileFlag = true;
    }
    foreach(const QString &file,files) {
        if(m_filePathList.contains(file)) {
            UIHelper::ShowMessageBoxError(tr("此文件已添加"));
            return;
        }
    }
    m_filePathList.append(files);
    showSelectedFiles();
}

void CreateTaskWidget::on_selectSrcDir(const QString &url)
{
    m_curSelectFiles.clear();
    if(m_filePathList.contains(url)) {
        UIHelper::ShowMessageBoxError(tr("此文件已添加"));
        return;
    }
    m_curSelectFiles.append(url);
    if(url.size() > 0) {
        fileFlag = true;
    }
    //保存目录的位置
    int index = m_filePathList.size();
    dirIndexList.append(index);
    m_filePathList.append(url);
    showSelectedFiles();
}

void CreateTaskWidget::on_selectWorkDir(const QString &dir)
{
    m_selectWorkDir = dir;
    if(m_selectWorkDir.lastIndexOf("/") == m_selectWorkDir.size() -1 )
    {
        m_selectWorkDir.resize(m_selectWorkDir.size() -1);
    }
}

bool CreateTaskWidget::loadDirFiles(const QString &path, const QString &srcPath, const QString &SavePath)
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
            loadDirFiles(info.path() + "/" + info.fileName(),srcPath,SavePath);

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

void CreateTaskWidget::on_btn_set_saveAbst_clicked()
{
    if(filesSelectRows.isEmpty()) {
        UIHelper::ShowMessageBoxError(tr("Please select a message"));
        return;
    }
    FileDirWidget* fileDir = new FileDirWidget;
    fileDir->setDefaultDir(m_defaultSaveDir);
    connect(fileDir,SIGNAL(evt_selectDir(QString)),this,SLOT(on_selectSaveDir(QString)));
    fileDir->show();
}

void CreateTaskWidget::on_btn_files_del_clicked()
{
    if(filesSelectRows.size() < 1) {
        return;
    }
    int ok = UIHelper::ShowMessageBoxQuesion(tr("你确定要删除记录吗?"));
    if(!ok) {
        return;
    }
    for(int row = filesSelectRows.size() -1; row > -1; --row) {
        m_filePathList.removeAt(row);
        ui->tw_files_content->removeRow(row);
        m_saveDirList.removeAt(row);
    }
    filesSelectRows.clear();
    if(m_filePathList.size() < 1) {
        fileFlag = false;
    }
}
