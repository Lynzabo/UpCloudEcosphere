#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H
#include <QtCore>
#include <QTableWidgetItem>
#include <QResizeEvent>
class TableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit TableWidget(QWidget *parent = 0);
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
     * @brief setItem   添加单元格数据
     * @param row
     * @param column
     * @param item
     */
    void setItem(int row, int column, QTableWidgetItem *item);
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
private:
    QMap<int,double> colsPercentages;
    //设置固定宽度的所有列
    QMap<int,int> colsFixedWidth;
    QMap<int,Qt::Alignment> colsAlignment;
};

#endif // TABLEWIDGET_H
