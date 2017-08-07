#ifndef TASKSCHEDULERCHAIN_H
#define TASKSCHEDULERCHAIN_H
#include "core/chain.h"
#include "filter/registry/actionregistryfactory.h"

class ACTIONLIBSHARED_EXPORT TaskSchedulerChain : public Chain
{
    Q_OBJECT
public:
    TaskSchedulerChain();
    virtual void invoke(RequestContext *request = 0,ResponseContext *response = 0, DataGramInfo *gram = 0);
};

#endif // TASKSCHEDULERCHAIN_H
