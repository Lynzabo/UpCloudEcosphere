#ifndef VCSCLIENTGROUPASSOC_H
#define VCSCLIENTGROUPASSOC_H

#include "cscgroupassoc.h"
class VCsClientGroupAssoc : public CsClientGroupAssoc
{
public:
    VCsClientGroupAssoc();
    QString getDescription() const;
    void setDescription(const QString &value);

private:
    QString description;
};

#endif // VCSCLIENTGROUPASSOC_H
