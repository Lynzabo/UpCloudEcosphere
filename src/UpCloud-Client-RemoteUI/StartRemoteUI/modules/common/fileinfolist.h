#ifndef FILEINFOLIST_H
#define FILEINFOLIST_H

#include <QWidget>
#include <QtCore>
#include <QMouseEvent>
#include <QMenu>
namespace Ui {
class FileInfoList;
}

class FileInfoList : public QWidget
{
    Q_OBJECT

public:
    enum TableHeaderElement {
        FILE_NAME,
        SRC_ABST,
        SAVE_ABST,
        WORK_ABST
    };
    explicit FileInfoList(QWidget *parent = 0);
    ~FileInfoList();

    QString defaultSaveDir() const;
    void setDefaultSaveDir(const QString &defaultSaveDir);
signals:
    void evt_selectedFileInfoList(const QStringList &srcList,const QStringList &saveAbst);

private:
    void initWindow();

    void loadDatas();

    void updateSaveAbst();
protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
private slots:

    /**
     * @brief on_selectedRow    选中1行
     * @param selectedRow
     */
    void on_selectedRow(int selectedRow);
    /**
     * @brief on_selectedRows   选中多行
     * @param selectedRows
     */
    void on_selectedRows(QList<int> selectedRows);
    /**
     * @brief on_doubleSelected 双击1行
     * @param selectedRow
     */
    void on_doubleSelected(int selectedRow);
    //启动选择文件界面
    void on_selectFileSrcAbst();
    //启动选择文件夹界面
    void on_selectDirSrcAbst();
    //选择保存路径
    void on_selectSaveDir(const QString &dir);
    //选择本地文件
    void on_selectSrcFiles(const QStringList &files);
    //选择目录
    void on_selectSrcDir(const QString &url);
    //选择工作目录
    void on_selectWorkDir(const QString &dir);

    void on_btn_select_file_clicked();

    void on_btn_del_file_clicked();

    void on_btn_set_save_path_clicked();

    void on_btn_save_clicked();

    void on_btn_cancel_clicked();

    bool loadDirFiles(const QString &path,const QString &srcPath,const QString &SavePath);

    void on_btn_menu_cancel_clicked();

private:
    Ui::FileInfoList *ui;
    //选中行
    QList<int> m_selectedRows;
    //文件来源信息列表
    QStringList m_filePathList;
    //选择保存目录
    QString m_selectSaveDir;
    //选择工作目录
    QString m_selectWorkDir;
    //选择本地目录
    QStringList m_srcDir;
    //默认保存目录
    QString m_defaultSaveDir;
    //保存目录链表
    QStringList m_saveDirList;
    //当前文件信息
    QStringList m_curSelectFiles;


    //文件保存路径列表
    QStringList m_saveAbst;
    //文件来源目录链表
    QStringList m_srcAbst;

    //选择菜单

    QMenu* m_menu;


    bool mousePressed;
    QPoint mousePoint;
};

#endif // FILEINFOLIST_H
