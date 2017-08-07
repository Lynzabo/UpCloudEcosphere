#ifndef PAGETABLEWIDGET_H
#define PAGETABLEWIDGET_H

#include <QWidget>
#include "page.h"
#include "ui_pagetablewidget.h"
namespace Ui {
class PageTableWidget;
}

class PageTableWidget : public QWidget,public Ui::PageTableWidget
{
    Q_OBJECT

public:
    explicit PageTableWidget(QWidget *parent = 0);
    ~PageTableWidget();
public:
    /**
     * @brief setPage   设置当前Page数据
     * @param page
     */
    void setPage(Page *page);
    /**
     * @brief setPageNavatorUsable  设置分页导航条可用
     * @param canUse
     */
    void setPageNavatorUsable(const bool &canUse = true);
private:
    /**
     * @brief updatePageNavatorInfo   修改分页导航条状态
     */
    void updatePageNavatorInfo();
signals:
    //选中表格体单行信号
    void evt_tableBodySelectedRow(int selectedRow);
    //选中多行信号
    void evt_tableBodySelectedRows(QList<int> selectedRows);
    //双击行信号
    void evt_tableBodyDoubleSelected(int selectedRow);
    //未选中信号
    void evt_tableBodySelectedNull();
    //分页表格联动信号
    void evt_pageTableAccept(const Page *page);
    //点击表头排序
    void evt_headerSort(int column,const QString &sortColName,Qt::SortOrder sord);
private slots:
    /**
     * @brief on_headerSort 点击表头排序
     * @param column
     * @param sortColName
     * @param sord
     */
    void on_headerSort(int column,const QString &sortColName,Qt::SortOrder sord);
    /**
     * @brief on_pbtn_pageFirst_clicked 显示首页
     */
    void on_pbtn_pageFirst_clicked();
    /**
     * @brief on_pbtn_pagePrev_clicked  显示上一页
     */
    void on_pbtn_pagePrev_clicked();
    /**
     * @brief on_pbtn_pageNext_clicked  显示下一页
     */
    void on_pbtn_pageNext_clicked();
    /**
     * @brief on_pbtn_pageEnd_clicked   显示尾页
     */
    void on_pbtn_pageEnd_clicked();
    /**
     * @brief on_btn_pageOk_clicked 确认第几页,每页显示条数
     */
    void on_btn_pageOk_clicked();
private:
    /**
     * @brief updatePageTableWidget    更新表格数据
     */
    void updatePageTableWidget();
private:
    Page *nowPage;
    void initWindow();
};

#endif // PAGETABLEWIDGET_H
