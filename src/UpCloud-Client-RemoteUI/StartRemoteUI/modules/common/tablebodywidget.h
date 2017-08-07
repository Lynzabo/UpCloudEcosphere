#ifndef TABLEBODYWIDGET_H
#define TABLEBODYWIDGET_H
#include <QtCore>
#include <QTableWidgetItem>
#include <QResizeEvent>
#include <QStyledItemDelegate>
#include <QWidget>
#include <QHeaderView>
#include <QPainter>
#include <QMouseEvent>

class TableBodyWidget : public QTableWidget
{
    Q_OBJECT
public:
    //排序类型
    enum Sorder {
        SORDER_ASC,
        SORDER_DESC,
    };
    explicit TableBodyWidget(QWidget *parent = 0);
    /**
     * @brief setHeaderColumnLabel  设置表头显示
     * @param column
     * @param text
     */
    void setHeaderColumnLabel(int column,const QString &text);
    /**
     * @brief setHeaderColumnWidth  设置表头的宽度,百分比设置
     * @param column
     * @param percentage    占整个宽度的百分比
     * setHeaderColumnWidth和setColumnWidth可以混合使用
     */
    void setHeaderColumnWidth(int column, double percentage);
    /**
     * @brief setColumnWidth    设置表头的宽度,固定值设置
     * @param column
     * @param width
     * setHeaderColumnWidth和setColumnWidth可以混合使用
     * 为保证不被调用QTableWidget的setColumnWidth,重载该函数
     */
    void setColumnWidth(int column, int width);
    /**
     * @brief setHeaderColumnWidth  设置表头的宽度,固定值设置
     * @param column
     * @param width
     * 为保持与百分比接口名称一致,定义此接口
     */
    void setHeaderColumnWidth(int column, int width);
    /**
     * @brief setHeaderColumnAlignment  设置表头对齐,如果不设置,则使用默认对齐Qt::AlignHCenter | Qt::AlignVCenter,表格内容跟随表头对齐变化
     * @param column
     * @param alignment
     */
    void setHeaderColumnAlignment(int column,Qt::Alignment alignment = Qt::AlignHCenter | Qt::AlignVCenter);
    /**
     * @brief setHeaderColumnCanSort    设置列可排序,默认为不可排序
     * @param column
     * @param sortColName   要排序名称,分页中orderFieldName存
     */
    void setHeaderColumnCanSort(int column,const QString sortColName);
    /**
     * @brief setDefaultAlignment 设置默认对齐，主要对齐跳转分页使用
     */
    void setDefaultAlignment();
private:
    void initWindow();

    // QWidget interface
protected:
    /**
     * @brief resizeEvent   重载窗口大小改变
     * @param e
     */
    virtual void resizeEvent(QResizeEvent *e);
Q_SIGNALS:
    //未选中信号
    void evt_selectedNull();
    //选中多行信号
    void evt_selectedRows(QList<int> selectedRows);
    //选中单行信号
    void evt_selectedRow(int selectedRow);
    //双击行信号
    void evt_doubleSelected(int selectedRow);
    //点击排序信号
    void evt_headerSort(int column,const QString &sortColName,Qt::SortOrder sord);
public Q_SLOTS:
    /**
     * @brief on_select    选中
     */
    void on_select();
    /**
     * @brief on_doubleClicked  双击行
     * @param index
     */
    void on_doubleClicked(const QModelIndex &index);
    /**
     * @brief on_horizontalHeaderClicked    表头单击
     * @param logicalIndex
     */
    void on_horizontalHeaderClicked(int logicalIndex);
private:
    QMap<int,double> colsPercentages;
    //设置固定宽度的所有列
    QMap<int,int> colsFixedWidth;
    QMap<int,Qt::Alignment> colsAlignment;
};

class TableHeaderView : public QHeaderView
{
    Q_OBJECT
public:
signals:
    //点击排序信号
    void evt_headerSort(int column,const QString &sortColName,Qt::SortOrder sord);
public slots:

public:
    explicit TableHeaderView(Qt::Orientation orientation, QWidget *parent = 0);
    /**
     * @brief setHeaderColumnCanSort    设置列可排序,默认为不可排序
     * @param column
     * @param sortColName   要排序名称,分页中orderFieldName存
     */
    void setHeaderColumnCanSort(int column,const QString sortColName);

protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent * event);

private:
    /**
     * @brief sectionRect   获取当前列的矩形区域
     * @param logicalIndex
     * @return
     */
    QRect sectionRect(int logicalIndex) const;
    /**
     * @brief drawSorderPixmap  绘制排序图标
     * @param painter
     * @param logicalIndex
     * @param enabled   滑动在上面
     */
    void drawSorderPixmap(QPainter *painter, int logicalIndex, bool enabled) const;
    QRect buttonMenuRect(int logicalIndex) const;
    /**
     * @brief initWindow    初始化窗口基本数据
     */
    void initWindow();
private:
    //缓存升序图标
//    QPixmap ascSortPixmap;
    //缓存降序图标
//    QPixmap descSortPixmap;
    //当前排序索引
    int curLogicalIndex;
    //排序类型
    Qt::SortOrder curSorder;
    //可排序列索引
    QMap<int,QString> canSortCols;

};


class TableNoFocusFrameDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit TableNoFocusFrameDelegate(QObject *parent = NULL);
    ~TableNoFocusFrameDelegate(){}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    TableNoFocusFrameDelegate& operator=(const TableNoFocusFrameDelegate& obj);
    TableNoFocusFrameDelegate(const TableNoFocusFrameDelegate& obj);

};
#endif // TABLEBODYWIDGET_H
