#include "pageutil.h"
#include "avro.h"
using QtJson::JsonObject;
using QtJson::JsonArray;

PageUtil::PageUtil()
{

}

bool PageUtil::pageEntityFromjsonStr(const QString &msg, Page &page, QString &resultStr)
{
    bool ok = false;
    JsonObject jsonResult = QtJson::parse(msg, ok).toMap();
    if (ok)
    {
        page.setCurPageNum((quint32)(jsonResult["page.curPageNum"].toInt()));
        page.setTotalCount((quint64)(jsonResult["page.totalCount"].toLongLong()));
        page.setNumPerPage((quint32)(jsonResult["page.numPerPage"].toInt()));
        page.setTotalPages((quint32)(jsonResult["page.totalPages"].toInt()));
        page.setOrderField((Qt::SortOrder)(jsonResult["page.orderField"].toInt()));
        page.setOrderFieldName(jsonResult["page.orderFieldName"].toString());
        resultStr = jsonResult["page.results"].toString();
    }
    return ok;
}

void PageUtil::pageEntityTojsonStr(const Page &page, const QString &resultStr, QString &msg)
{
    JsonObject objJson;
    objJson["page.curPageNum"] = page.getCurPageNum();
    objJson["page.totalCount"] = page.getTotalCount();
    objJson["page.numPerPage"] = page.getNumPerPage();
    objJson["page.totalPages"] = page.getTotalPages();
    objJson["page.orderField"] = page.getOrderField();
    objJson["page.orderFieldName"] = page.getOrderFieldName();
    objJson["page.results"] = resultStr;
    msg = QtJson::serialize(objJson);
}
