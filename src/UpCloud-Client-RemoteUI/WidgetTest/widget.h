#ifndef WIDGET_H
#define WIDGET_H
#include <QtCore>
#include <QTime>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include "ftpclientpool.h"
#include "downview.h"
#include "upview.h"
#include "downthread.h"
#include <QFileDialog>
#include "upthread.h"
#include "ffiledialog.h"
namespace Ui {
class Widget;
}

class  Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void setThreadConnectFtp();
    ~Widget();
    void initWidget();
    void showDownViewList();
    void showUpViewList();

    //初始化参数
    void initWindow();
    //设置pathname中的文件名
    void setDownFileNameList(const QStringList &list);
    void setUpFileNameList(const QStringList &list);
    QStringList fileList() const;
    //设置文件名列表
    void setFileList(const QStringList &fileList);
    void addFileDown(const QString &fileUrl);
private slots:
    //上传/下载等开始信号
    void on_downStart();
    //一个文件上传/下载完成信号
    void on_downSubFileEnd(const QString &taskID,const QString &fileUrl,const QString &destAbst);
    //上传/下载等结束信号
    void on_downEnd(const QString &taskID);
    void on_downProcess(const QString &fileUrl,const quint64 &haveDoneBytes,const quint64 &totalBytes);
    //操作出错信号
    void on_downError(const QString &taskID,const QString &src,const QString &errMsg);
    //删除一条记录重新布局
    void on_downDelItem(DownView *item);

    void on_selectedSrcAbst(const QStringList &src);
    //上传/下载等开始信号
    void on_upStart();
    //一个文件上传/下载完成信号
    void on_upSubFileEnd(const QString &taskID,const QString &fileUrl,const QString &destAbst);
    //上传/下载等结束信号
    void on_upEnd(const QString &taskID);
    void on_upProcess(const QString &fileUrl,const quint64 &haveDoneBytes,const quint64 &totalBytes);
    void on_upError(const QString &taskID,const QString &src,const QString &errMsg);

    void on_down();

    //删除一条记录重新布局
    void on_upDelItem(UpView *item);


    void on_up();

    void on_m_down_start_clicked();

    void on_m_down_end_clicked();

    void on_m_up_start_clicked();

    void on_m_up_end_clicked();

private:
    Ui::Widget *ui;
    NetTransClient* m_ftpPool;
    NetTransClient* m_ftpUpPool;
    //FTP 源文件 以及保存文件
    QMap<QString,QString> m_downGroupFile;
    QList<DownView*> m_downViewList;
    QMap<QString,DownView*> m_downFileView;
    //文件名列表
    QStringList m_downFileList;
    //源文件名列表
    QStringList m_downNameList;
    //路径名列表
    QStringList m_downFilePath;
    QVBoxLayout* m_downVlayout;
    QHBoxLayout* m_downHlayout;

    QMap<QString,QString> m_upGroupFile;
    QList<UpView*> m_upViewList;
    QMap<QString,UpView*> m_upFileView;
    //文件名列表
    QStringList m_upFileList;
    //源文件名列表
    QStringList m_upNameList;
    //路径名列表
    QStringList m_upFilePath;
    QVBoxLayout* m_upVlayout;
    QHBoxLayout* m_upHlayout;

    DownThread* downthread;
    UpThread*  upthread;
    FFileDialog* fileDlg;
    QStringList srcAbstList;
};

#endif // WIDGET_H
