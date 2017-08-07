#include "page.h"

Page::Page()
{
    this->curPageNum = (quint32)1;
    this->numPerPage = (quint32)10;
    this->orderField = Qt::DescendingOrder;
    this->orderFieldName.clear();
    this->totalPages = (quint32)0;
    this->totalCount = (quint64)0;
    this->results.clear();
}

bool Page::isEmpty()
{
    return orderFieldName.isEmpty() &&
            totalPages == (quint32)0 &&
            totalCount == (quint64)0 &&
            !results.size();
}
QList<QVariantMap> Page::getResults() const
{
    return results;
}

void Page::setResults(const QList<QVariantMap> &_results)
{
    results = _results;
}

quint64 Page::getTotalCount() const
{
    return totalCount;
}

void Page::setTotalCount(const quint64 &_totalCount)
{
    totalCount = _totalCount;
}

quint32 Page::getTotalPages() const
{
    return totalPages;
}

void Page::setTotalPages(const quint32 &_totalPages)
{
    totalPages = _totalPages;
}

QString Page::getOrderFieldName() const
{
    return orderFieldName;
}

void Page::setOrderFieldName(const QString &_orderFieldName)
{
    orderFieldName = _orderFieldName;
}


void Page::setOrderField(const Qt::SortOrder &_orderField)
{
    orderField = _orderField;
}

quint32 Page::getNumPerPage() const
{
    return numPerPage;
}

void Page::setNumPerPage(const quint32 &_numPerPage)
{
    numPerPage = _numPerPage;
}

Qt::SortOrder Page::getOrderField() const
{
    return orderField;
}

quint32 Page::getCurPageNum() const
{
    return curPageNum;
}

void Page::setCurPageNum(const quint32 &_curPageNum)
{
    curPageNum = _curPageNum;
}

