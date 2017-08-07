#ifndef PAGE_H
#define PAGE_H
#include <QtCore>
#include "ermlib_global.h"

/**
 * @brief The Page class    分页对象封装
 */
class ERMLIBSHARED_EXPORT Page
{
public:
    Page();
    /**
     * @brief isEmpty   Page是否为空
     * @return
     */
    bool isEmpty();
private:
    //当前页码
    quint32 curPageNum;
    //每页显示条数
    quint32 numPerPage;
    //倒序还是正序
    Qt::SortOrder orderField;
    //排序字段名
    QString orderFieldName;
    //总页数
    quint32 totalPages;
    //所有记录总条数
    quint64 totalCount;
    //记录
    QList<QVariantMap> results;
public:
    /**
     * @brief getCurPageNum 获取当前页码
     * @return
     */
    quint32 getCurPageNum() const;
    /**
     * @brief setCurPageNum 设置当前页码
     * @param _curPageNum 当前页码
     */
    void setCurPageNum(const quint32 &_curPageNum = (quint32)1);
    /**
     * @brief getNumPerPage 获得每页显示条数
     * @return
     */
    quint32 getNumPerPage() const;
    /**
     * @brief setNumPerPage 设置每页显示条数
     * @param _numPerPage
     */
    void setNumPerPage(const quint32 &_numPerPage = (quint32)10);
    /**
     * @brief getOrderField 获得是倒序还是正序
     * @return
     */
    Qt::SortOrder getOrderField() const;
    /**
     * @brief setOrderField 设置是倒序还是正序
     * @param _orderField
     */
    void setOrderField(const Qt::SortOrder &_orderField = Qt::DescendingOrder);
    /**
     * @brief getOrderFieldName 获得排序字段名
     * @return
     */
    QString getOrderFieldName() const;
    /**
     * @brief setOrderFieldName 设置排序字段名
     * @param _orderFieldName
     */
    void setOrderFieldName(const QString &_orderFieldName);
    /**
     * @brief getTotalPages 获得总页数
     * @return
     */
    quint32 getTotalPages() const;
    /**
     * @brief setTotalPages 设置总页数
     * @param _totalPages
     */
    void setTotalPages(const quint32 &_totalPages = 0);
    /**
     * @brief getTotalCount 获得记录总条数
     * @return
     */
    quint64 getTotalCount() const;
    /**
     * @brief setTotalCount 设置记录总条数
     * @param _totalCount
     */
    void setTotalCount(const quint64 &_totalCount = 0);
    /**
     * @brief getResults    获得结果集
     * @return
     */
    QList<QVariantMap> getResults() const;
    /**
     * @brief setResults    设置结果集
     * @param _results
     */
    void setResults(const QList<QVariantMap> &_results);
};

#endif // PAGE_H
