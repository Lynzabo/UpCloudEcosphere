#include "filedialog.h"

FileDialog::FileDialog()
{
    initWindow();
}

void FileDialog::initWindow()
{
    this->setFileMode(QFileDialog::ExistingFiles);
    this->setAcceptMode(QFileDialog::AcceptOpen);
    this->setAttribute(Qt::WA_ShowModal,true);
    this->setViewMode(QFileDialog::Detail);
    this->setDirectory("./");
    //设置目录过滤
    this->setFilter(QDir::Executable);
    //设置类型过滤
    this->setNameFilter("*.*");


}
