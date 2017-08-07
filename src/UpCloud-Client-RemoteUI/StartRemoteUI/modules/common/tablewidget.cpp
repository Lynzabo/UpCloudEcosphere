#include "tablewidget.h"
#include "nofocusframedelegate.h"
#include <QHeaderView>
#include "headerview.h"
TableWidget::TableWidget(QWidget *parent) : QTableWidget(parent)
{
    colsPercentages.clear();
    colsFixedWidth.clear();
    colsAlignment.clear();
    initWindow();
}
void TableWidget::initWindow()
{
    //加全选反选,获取选中项目
    //设置表格不可编辑
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置表格字体和大小
    this->setFont(QFont("Helvetica",9,3));
    //设置无边框
    this->setFrameShape(QFrame::NoFrame);
    //设置不显示虚框
    this->setItemDelegate(new NoFocusFrameDelegate());
    //开启捕获鼠标功能
    this->setMouseTracking(true);
    //选中时直接选中行
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置允许选中多个
    this->setSelectionMode(QAbstractItemView::ExtendedSelection);
    //隐藏垂直表头
    this->verticalHeader()->setVisible(false);
    //设置选中行颜色
//    this->setStyleSheet("selection-background-color:#efefef");
    //奇数偶数行不同背景色
    this->setAlternatingRowColors(true);
    //设置水平表头
    //选中时,对水平的表头不加高亮
    this->horizontalHeader()->setHighlightSections(false);
    //对最后一列加拉伸到铺满表格
    this->horizontalHeader()->setStretchLastSection(true);
    //    //设置将行的大小设为与内容相匹配
    //tableWidget->resizeColumnsToContents();
    //设置表头列默认宽度
    //this->horizontalHeader()->setDefaultSectionSize(150);
    //添加自定义表头
    HeaderView *myHeader=new HeaderView(Qt::Horizontal,this);
    this->setHorizontalHeader(myHeader);
    //    this->horizontalHeader()->setFixedWidth(300);
    //设置表头高度
    this->horizontalHeader()->setFixedHeight(35);
    //设置水平表头默认对其方式,并在resizeEvent处置内容列与表头列对齐方式一样,如果在应用时又单独指定了某一列的对齐方式,则改列会按照最新的使用
    this->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    //设置垂直行高
    //this->verticalHeader()->setDefaultSectionSize(30);
    //设置水平表头显示排序,设置排序可用
    //this->horizontalHeader()->setSortIndicatorShown(true);
    //使用点击信号获取选中的行
    connect(this,&TableWidget::itemSelectionChanged,this,&TableWidget::on_select);
    connect(this,&TableWidget::doubleClicked,this,&TableWidget::on_doubleClicked);
}

void TableWidget::resizeEvent(QResizeEvent *e)
{
    //获取窗口大小改变时表格真实宽度
    int tWidth = e->size().width();
    int tHeight = e->size().height();
    Q_UNUSED(tHeight)
    int hasWidth = 0;
    //设置固定宽度的列的宽高
    if(colsFixedWidth.size()>0)
    {
        QList<int> cols = colsFixedWidth.keys();
        for(int col:cols)
        {
            int colWidth = colsFixedWidth.value(col);
            QTableWidget::setColumnWidth(col,colWidth);
            hasWidth +=colWidth;
        }
    }
    tWidth -= hasWidth;
    //设置百分比的列的宽高
    if(colsPercentages.size()>0)
    {
        QList<int> cols = colsPercentages.keys();
        for(int col:cols)
        {
            double *pers = new double;
            *pers = colsPercentages.value(col);
            if(*pers <= 0)
            {
                *pers = 0;
            }
            QTableWidget::setColumnWidth(col,tWidth*(*pers));
            delete pers;
        }
    }
    //设置表头及其内容每列的对齐方式
    //获取默认对齐
    Qt::Alignment defaultAlign = this->horizontalHeader()->defaultAlignment();
    int tcols = this->horizontalHeader()->count();
    int trows = this->verticalHeader()->count();
    for(int col = 0; col <tcols; col++)
    {
        Qt::Alignment align;
        if(colsAlignment.contains(col))
        {
            align = colsAlignment.value(col);
        }
        else
        {
            align = defaultAlign;
        }
        //设置表头列对齐
        this->horizontalHeaderItem(col)->setTextAlignment(align);
        //设置该列每行对齐
        for(int row = 0; row <trows;row++)
        {
            this->item(row,col)->setTextAlignment(align);
        }
    }
}

void TableWidget::on_select()
{
    QList<int> selectedRows;selectedRows.clear();
    QList<QTableWidgetSelectionRange> ranges = this->selectedRanges();
    int count = ranges.count();
    for(int i = 0;i<count;i++)
    {
        int topRow = ranges.at(i).topRow();
        int bottomRow = ranges.at(i).bottomRow();
        for(int j = topRow;j <= bottomRow;j++)
        {
            selectedRows.append(j);
        }
    }
    if(selectedRows.size()>0)
    {
        if(selectedRows.size() == 1)
        {
            emit
                evt_selectedRow(selectedRows.at(0));
        }
        else
        {
            emit
                evt_selectedRows(selectedRows);
        }
    }
    else
    {
        evt_selectedNull();
    }
}

void TableWidget::on_doubleClicked(const QModelIndex &index)
{
    emit
        evt_doubleSelected(index.row());
}

void TableWidget::setColumnWidth(int column, int width)
{
    colsFixedWidth.insert(column,width);
}

void TableWidget::setHeaderColumnWidth(int column, int width)
{
    setColumnWidth(column,width);
}

void TableWidget::setHeaderColumnAlignment(int column, Qt::Alignment alignment)
{
    colsAlignment.insert(column,alignment);
}

void TableWidget::setItem(int row, int column, QTableWidgetItem *item)
{
    Qt::Alignment align;
    if(colsAlignment.keys().contains(column))
    {
        align = colsAlignment.value(column);
    }
    else
    {
        align = this->horizontalHeader()->defaultAlignment();
    }
    item->setTextAlignment(align);
    QTableWidget::setItem(row,column,item);
}

void TableWidget::setHeaderColumnWidth(int column, double percentage)
{
    colsPercentages.insert(column,percentage);
}

