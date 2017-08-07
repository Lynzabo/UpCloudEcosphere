#include "duplexutil.h"
#include "server/interceptor/registry/fduplexregistryfactory.h"
using namespace Environment::Datagram::UI_Ctrl::Opera_Type;
DuplexUtil::DuplexUtil()
{

}

bool DuplexUtil::addrIsLegal(const quint16 &ExecType)
{
    return FDuplexRegistryFactory::contains(ExecType);
}

