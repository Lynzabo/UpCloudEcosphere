#include "vcscgroupassoc.h"

VCsClientGroupAssoc::VCsClientGroupAssoc()
{

}

QString VCsClientGroupAssoc::getDescription() const
{
    return description;
}

void VCsClientGroupAssoc::setDescription(const QString &value)
{
    description = value;
}

