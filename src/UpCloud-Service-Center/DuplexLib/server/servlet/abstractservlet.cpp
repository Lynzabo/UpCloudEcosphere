#include "abstractservlet.h"

AbstractServlet::AbstractServlet()
{

}

void AbstractServlet::doInit()
{
    qDebug() << "Request init";
}

void AbstractServlet::doExec(DRequestContext *request, DResponseContext *response)
{
    qDebug() << "Request doExec";
}

void AbstractServlet::doDestory()
{
    qDebug() << "Request doDestory";
}

