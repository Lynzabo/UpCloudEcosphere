#ifndef SELECTDICTWIDGET_H
#define SELECTDICTWIDGET_H

#include <QWidget>
#include <QtCore>
#include <QPushButton>
#include "erm.h"
#include "../../UpCloud-Service-Center/BusinessIServer/BasalIServer/bean/csdict.h"
#include "../FrontBusinessIRemoteUI/BasalOperaIRemoteUI/basaloperairemoteui.h"
#include "baseiremote.h"
#include "adddictwidget.h"
namespace Ui {
class SelectDictWidget;
}

class SelectDictWidget : public QWidget
{
    Q_OBJECT

public:
    enum TableHeaderElement {
        INDEX,
        CODE,
        NAME,
        DESCRIPTION,
        STATE,
        SEQUENCE,
        INSERT_TIME,
        INSERTER
    };
    explicit SelectDictWidget(QWidget *parent = 0);
    ~SelectDictWidget();
    //获取字典父级的名字
    QString getDictParentName(const CsDict & dict);
signals:
    void evt_reload();
    void evt_delDicts(const QList<QString> uuids);
    void evt_addDict(const CsDict &dict);
private slots:
    /**
     * @brief on_doubleTree 双击树图中的项目
     * @param uuid  选中字典中的UUID
     */
    void on_itemClicked(const QString &uuid, const QString &name);
    /**
     * @brief on_tableBodySelectedRow 单选
     */
    void on_tableBodySelectedRow(int selectedRow);
    /**
     * @brief on_tableBodySelectedRows 多选
     */
    void on_tableBodySelectedRows(QList<int> selectedRows);
    /**
     * @brief on_tableBodyDoubleSelected 双击
     */
    void on_tableBodyDoubleSelected(int selectedRow);

    /**
     * @brief on_tableBodySelectedNull  未选中表格体信号
     */
    void on_tableBodySelectedNull();

    /**
     * @brief on_pageTableAccept    分页表格联动信号
     * @param page
     */
    void on_pageTableAccept(const Page *page);

    /**
     * @brief on_foldered  折叠
     */
    void on_foldered();
    void on_itemtaskCallback(const qint32 msgId, const QString &msg);
    void on_itemtaskCallback(const qint32 msgId, const QString &msg,CsDict dict);
    void on_itemtaskCallback(const qint32 msgId, const QString &msg, const QList<CsDict> &dictList);

    void on_btn_select_clicked();
    void on_btn_new_clicked();

    void on_btn_del_clicked();

    void on_cb_set_state_currentIndexChanged(int index);

    void on_addWidgetOkForNew(bool flg);

    void on_addWidgetOkForOpen(bool flg);

    void on_btn_open_clicked();


    void on_btn_folder_clicked();

private:
    //初始化窗口参数
    void initWindow();
    //初始化数据
    void initDatas();

    void loadComboBoxText();
private:
    Ui::SelectDictWidget *ui;
    bool m_folder;
    QWidget* m_parent;
    QList<CsDict> m_dictList;
    QStringList selectedUuids;
    QList<int> m_selctedRows;
    QString m_uuid;
    //编辑信息的参数
    CsDict m_dict;
    //编辑字典时用于保存编辑前的顺序
    qint32 sequenceOld;
    //分页信息
    Page* m_page;


    QPoint oldPos;
    QPoint newPos;
    QPushButton* newBtn;

};

#endif // SELECTDICTWIDGET_H
