#ifndef MOVEGROUPSEQUENCESERVLET_H
#define MOVEGROUPSEQUENCESERVLET_H
#include <QtCore>
#include "base.h"
#include "duplex.h"
#include "avro.h"
#include "basaloperaiserver_global.h"

class BASALOPERAISERVERSHARED_EXPORT MoveGroupSequenceServlet : public AbstractServlet
{
public:
    MoveGroupSequenceServlet();
    /**
     * @brief doExec
     * @param request
     * @param response
     */
    void doExec(DRequestContext *request , DResponseContext *response );
};

#endif // MOVEGROUPSEQUENCESERVLET_H
