#include "pagetablewidget.h"

PageTableWidget::PageTableWidget(QWidget *parent) :
    QWidget(parent),nowPage(new Page)
{
    this->setupUi(this);
    initWindow();
}

PageTableWidget::~PageTableWidget()
{
    delete nowPage;
}

void PageTableWidget::initWindow()
{
    //没有任何数据时的状态
    this->l_curPage->setText(QString::number(0));
    this->l_totalPage->setText(QString::number(0));
    this->l_totalNum->setText(QString::number(0));
    //广播选中1行
    connect(this->table_body,&TableBodyWidget::evt_selectedRow,this,&PageTableWidget::evt_tableBodySelectedRow);
    //广播选中多行
    connect(this->table_body,&TableBodyWidget::evt_selectedRows,this,&PageTableWidget::evt_tableBodySelectedRows);
    //广播双击1行
    connect(this->table_body,&TableBodyWidget::evt_doubleSelected,this,&PageTableWidget::evt_tableBodyDoubleSelected);
    //广播选中空白区域
    connect(this->table_body,&TableBodyWidget::evt_selectedNull,this,&PageTableWidget::evt_tableBodySelectedNull);
    //表头排序
    connect(this->table_body,&TableBodyWidget::evt_headerSort,this,&PageTableWidget::on_headerSort);
}

void PageTableWidget::setPage(Page *page)
{
    this->nowPage = page;
    //修改分页导航条数据及状态
    updatePageNavatorInfo();
}

void PageTableWidget::setPageNavatorUsable(const bool &canUse)
{
    this->table_pageNavator->setVisible(canUse);
}

void PageTableWidget::on_pbtn_pageFirst_clicked()
{
    //跳至首页
    this->nowPage->setCurPageNum(1);
    updatePageTableWidget();
}

void PageTableWidget::on_pbtn_pagePrev_clicked()
{
    //跳至上一页
    if(this->nowPage->getCurPageNum() == 1) {
        return;
    }
    this->nowPage->setCurPageNum(this->nowPage->getCurPageNum()-1);
    updatePageTableWidget();
}

void PageTableWidget::on_pbtn_pageNext_clicked()
{
    //跳至下一页
    if(this->nowPage->getCurPageNum() == this->nowPage->getTotalPages()) {
        return;
    }
    this->nowPage->setCurPageNum(this->nowPage->getCurPageNum()+1);
    updatePageTableWidget();
}

void PageTableWidget::on_pbtn_pageEnd_clicked()
{
    //跳至尾页
    this->nowPage->setCurPageNum(this->nowPage->getTotalPages());
    updatePageTableWidget();
}

void PageTableWidget::on_btn_pageOk_clicked()
{
    //跳至指定页
    this->nowPage->setCurPageNum((quint32)this->sb_curPage->text().toInt());
    this->nowPage->setNumPerPage((quint32)this->sb_curPageNum->text().toInt());
    int count = this->nowPage->getTotalCount();
    int numPerPage = this->nowPage->getNumPerPage();
    if(count%numPerPage == 0) {
        this->nowPage->setTotalPages(count/numPerPage);
    }
    else {
        this->nowPage->setTotalPages(count/numPerPage + 1 );
    }
    if(this->nowPage->getCurPageNum() > this->nowPage->getTotalPages()) {
        this->nowPage->setCurPageNum(1);
    }
    updatePageTableWidget();
}

void PageTableWidget::updatePageTableWidget()
{

    updatePageNavatorInfo();
    //触发表格联动
    emit
        evt_pageTableAccept(this->nowPage);
}

void PageTableWidget::updatePageNavatorInfo()
{
    //TODO  修改状态
    //如果总页数==1
    if(nowPage->getTotalPages() == 1)
    {
        this->w_pages->setVisible(false);
        this->w_pos->setVisible(false);
        this->w_curNums->setVisible(false);
        this->btn_pageOk->setVisible(false);
        this->l_curPage->setText(QString::number(1));
        this->l_totalPage->setText(QString::number(1));
        this->l_totalNum->setText(QString::number(nowPage->getTotalCount()));
    }
    //如果总页数>1
    else
    {
        this->w_pages->setVisible(true);
        this->w_pos->setVisible(true);
        this->w_curNums->setVisible(true);
        this->btn_pageOk->setVisible(true);
        //修改最多可以选择跳转至最大页
        this->sb_curPage->setMaximum(nowPage->getTotalPages());
        //修改最多可以单页显示条数不超过总条数
        this->sb_curPageNum->setMaximum(nowPage->getTotalCount());
        //如果当前为第一页
        if(nowPage->getCurPageNum() == 1)
        {
            this->pbtn_pagePrev->setVisible(false);
        }
        else {
            this->pbtn_pagePrev->setVisible(true);
        }
        //如果当前为最后一页
        if(nowPage->getCurPageNum() == nowPage->getTotalPages())
        {
            this->pbtn_pageNext->setVisible(false);
        }
        else {
            this->pbtn_pageNext->setVisible(true);
        }

        //修改页码为当前页
        sb_curPage->setValue(this->nowPage->getCurPageNum());
        sb_curPageNum->setValue(this->nowPage->getNumPerPage());
        this->l_curPage->setText(QString::number(nowPage->getCurPageNum()));
        this->l_totalPage->setText(QString::number(nowPage->getTotalPages()));
        this->l_totalNum->setText(QString::number(nowPage->getTotalCount()));
    }
}

void PageTableWidget::on_headerSort(int column, const QString &sortColName, Qt::SortOrder sord)
{
    Q_UNUSED(column)
    this->nowPage->setOrderFieldName(sortColName);
    this->nowPage->setOrderField(sord);
    //排序回到首页
    this->nowPage->setCurPageNum(1);
    updatePageTableWidget();
}
