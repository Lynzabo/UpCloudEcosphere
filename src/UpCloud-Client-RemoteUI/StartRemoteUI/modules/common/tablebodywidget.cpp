#include "tablebodywidget.h"
TableBodyWidget::TableBodyWidget(QWidget *parent) : QTableWidget(parent)
{
    colsPercentages.clear();
    colsFixedWidth.clear();
    colsAlignment.clear();
    initWindow();
}

void TableBodyWidget::setHeaderColumnLabel(int column, const QString &text)
{
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setText(text);
    this->setHorizontalHeaderItem(column,item);
}
void TableBodyWidget::initWindow()
{
    //加全选反选,获取选中项目
    //设置表格不可编辑
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置表格字体和大小
    this->setFont(QFont("Helvetica",9,3));
    //设置无边框
    this->setFrameShape(QFrame::NoFrame);
    //设置不显示虚框
    this->setItemDelegate(new TableNoFocusFrameDelegate());
    //开启捕获鼠标功能
    this->setMouseTracking(true);
    //选中时直接选中行
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置允许选中多个
    this->setSelectionMode(QAbstractItemView::ExtendedSelection);
    //隐藏垂直表头
    this->verticalHeader()->setVisible(false);
    //设置选中行颜色
    //this->setStyleSheet("selection-background-color:pink");
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
    TableHeaderView *myHeader=new TableHeaderView(Qt::Horizontal,this);
    this->setHorizontalHeader(myHeader);
    //点击排序事件
    connect(myHeader,&TableHeaderView::evt_headerSort,this, &TableBodyWidget::evt_headerSort);
    //    this->horizontalHeader()->setFixedWidth(300);

    //设置表头可点击
    //this->horizontalHeader()->setSectionsClickable(true);
    //设置表头高度
    this->horizontalHeader()->setFixedHeight(35);
    //设置水平表头默认对其方式,并在resizeEvent处置内容列与表头列对齐方式一样,如果在应用时又单独指定了某一列的对齐方式,则改列会按照最新的使用
    this->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    //设置垂直行高
    //this->verticalHeader()->setDefaultSectionSize(30);
    //设置水平表头显示排序,设置排序可用
    //this->horizontalHeader()->setSortIndicatorShown(true);
    //使用点击信号获取选中的行
    connect(this,&TableBodyWidget::itemSelectionChanged,this,&TableBodyWidget::on_select);
    connect(this,&TableBodyWidget::doubleClicked,this,&TableBodyWidget::on_doubleClicked);

}

void TableBodyWidget::resizeEvent(QResizeEvent *e)
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

void TableBodyWidget::on_select()
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

void TableBodyWidget::on_doubleClicked(const QModelIndex &index)
{
    emit
      evt_doubleSelected(index.row());
}

void TableBodyWidget::on_horizontalHeaderClicked(int logicalIndex)
{
    qDebug() << "click header:" <<logicalIndex;
}

void TableBodyWidget::setColumnWidth(int column, int width)
{
    colsFixedWidth.insert(column,width);
}

void TableBodyWidget::setHeaderColumnWidth(int column, int width)
{
    setColumnWidth(column,width);
}

void TableBodyWidget::setHeaderColumnAlignment(int column, Qt::Alignment alignment)
{
    colsAlignment.insert(column,alignment);
}

void TableBodyWidget::setHeaderColumnCanSort(int column,const QString sortColName)
{
    TableHeaderView *myHeader= qobject_cast<TableHeaderView*>(this->horizontalHeader());
    myHeader->setHeaderColumnCanSort(column,sortColName);
}

void TableBodyWidget::setDefaultAlignment()
{
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

void TableBodyWidget::setHeaderColumnWidth(int column, double percentage)
{
    colsPercentages.insert(column,percentage);
}

TableHeaderView::TableHeaderView(Qt::Orientation orientation, QWidget *parent)
    : QHeaderView(orientation, parent),curLogicalIndex(-1),curSorder(Qt::AscendingOrder)
{
    initWindow();
}

void TableHeaderView::setHeaderColumnCanSort(int column, const QString sortColName)
{
    canSortCols.insert(column,sortColName);
}

void TableHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->save();

    QHeaderView::paintSection(painter, rect, logicalIndex);

    painter->restore();

    if (!rect.isValid())
        return;
    QPoint pos = mapFromGlobal(QCursor::pos());
    drawSorderPixmap(painter, logicalIndex, buttonMenuRect(logicalIndex).contains(pos));
}
void TableHeaderView::mouseMoveEvent(QMouseEvent * event)
{
    QHeaderView::mouseMoveEvent(event);

    // Required to refresh the button menu enable/disable state.
    int logicalIndex = logicalIndexAt(event->pos());
    //获取鼠标所在表头单元格
    updateSection(logicalIndex);
}
void TableHeaderView::drawSorderPixmap(QPainter *painter, int logicalIndex, bool enabled) const
{
    //如果指定的可排序列为空,或不为空时不包含当前列
    if(canSortCols.size()<=0 || !canSortCols.contains(logicalIndex))
        return;
    QRect brect = buttonMenuRect(logicalIndex);

    painter->setPen(enabled ? QColor(186,186,186) : QColor(223, 223, 223));
    painter->setBrush(QColor(246,246,246));
    //painter->drawRect(brect.adjusted(0,0,-1,-1));

    painter->setPen(enabled ? QColor(71,71,71) : QColor(193, 193, 193));
    if(curLogicalIndex == -1 || logicalIndex != curLogicalIndex || (logicalIndex == curLogicalIndex && curSorder==Qt::DescendingOrder))
    {
        //向下箭头  降序DESC
        //从上往下五条横线加一个点
        painter->drawLine(brect.left()+1, brect.top()+3, brect.right()-1, brect.top()+3);
        painter->drawLine(brect.left()+2, brect.top()+4, brect.right()-2, brect.top()+4);
        painter->drawLine(brect.left()+3, brect.top()+5, brect.right()-3, brect.top()+5);
        painter->drawLine(brect.left()+4, brect.top()+6, brect.right()-4, brect.top()+6);
        painter->drawLine(brect.left()+5, brect.top()+7, brect.right()-5, brect.top()+7);
        painter->drawPoint(brect.left()+6, brect.top()+8);
    }
    else
    {
        //向上箭头  升序ASC
        //从上往下一个点加五条横线
        painter->drawPoint(brect.left()+6, brect.top()+3);
        painter->drawLine(brect.left()+5, brect.top()+4, brect.right()-5, brect.top()+4);
        painter->drawLine(brect.left()+4, brect.top()+5, brect.right()-4, brect.top()+5);
        painter->drawLine(brect.left()+3, brect.top()+6, brect.right()-3, brect.top()+6);
        painter->drawLine(brect.left()+2, brect.top()+7, brect.right()-2, brect.top()+7);
        painter->drawLine(brect.left()+1, brect.top()+8, brect.right()-1, brect.top()+8);
    }
}
//void HeaderView::drawSorderPixmap(QPainter *painter, int logicalIndex, bool enabled) const
//{
//    /*
//    QRect brect = buttonMenuRect(logicalIndex);

//    painter->setPen(enabled ? QColor(186,186,186) : QColor(223, 223, 223));
//    painter->setBrush(QColor(246,246,246));
//    painter->drawRect(brect.adjusted(0,0,-1,-1));

//    painter->setPen(enabled ? QColor(71,71,71) : QColor(193, 193, 193));
//    painter->drawLine(brect.left()+3, brect.top()+5, brect.right()-3, brect.top()+5);
//    painter->drawLine(brect.left()+4, brect.top()+6, brect.right()-4, brect.top()+6);
//    painter->drawLine(brect.left()+5, brect.top()+7, brect.right()-5, brect.top()+7);
//    painter->drawPoint(brect.left()+6, brect.top()+8);
//    */
//    QRect sr = sectionRect(logicalIndex);
////    QRect adjustRect = brect.adjusted(0,0,-1,-1);

//    //pix = pix.scaled(width*0.97,height*0.97,Qt::KeepAspectRatio);
//    qreal width = ascSortPixmap.width();
//    qreal height = ascSortPixmap.height();
//    QRect brect = QRect(sr.right()-sr.width()*1/3, sr.center().y()-height/2.0, width,height);
//    /*
//    QRect brect = buttonMenuRect(logicalIndex);
//    //将图片的宽和高都扩大两倍，并且在给定的矩形内保持宽高的比值
//    */
//    painter->drawPixmap(brect,ascSortPixmap);
//}

QRect TableHeaderView::buttonMenuRect(int logicalIndex) const
{
    QRect sr = sectionRect(logicalIndex);

    return QRect(sr.right() - 5 - 13, sr.center().y() - 6, 13, 13);
}

void TableHeaderView::initWindow()
{
}
QRect TableHeaderView::sectionRect(int logicalIndex) const
{
    return QRect(sectionViewportPosition(logicalIndex), 0, sectionSize(logicalIndex), height());
}

void TableHeaderView::mousePressEvent(QMouseEvent *event)
{
    /*
    if (isEnabled() && logicalIndexAt(event->pos()) == 0)
    {
        updateSection(0);
    }
    else QHeaderView::mousePressEvent(event);
*/
    QHeaderView::mousePressEvent(event);
    if (!isEnabled())
    {
        return;
    }
    int tmpLogicalIndex = logicalIndexAt(event->pos());
    if(canSortCols.size()<=0 || !canSortCols.contains(tmpLogicalIndex))
    {
        return;
    }
    //如果上次排序的不是当前字段,修改排序为默认
    if(tmpLogicalIndex != curLogicalIndex)
        curSorder = Qt::AscendingOrder;
    else
        curSorder = curSorder == Qt::AscendingOrder?Qt::DescendingOrder:Qt::AscendingOrder;
    curLogicalIndex = tmpLogicalIndex;
    updateSection(curLogicalIndex);
    emit
        evt_headerSort(tmpLogicalIndex,canSortCols.value(tmpLogicalIndex),curSorder);
}

TableNoFocusFrameDelegate::TableNoFocusFrameDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}
/*
 * Reimplemented the virtual function QStyledItemDelegate::paint()
 */
void TableNoFocusFrameDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem itemOption(option);
    // remove the focus state
    if (itemOption.state & QStyle::State_HasFocus)
    {
        itemOption.state ^= QStyle::State_HasFocus;
    }
    QStyledItemDelegate::paint(painter, itemOption, index);
}
