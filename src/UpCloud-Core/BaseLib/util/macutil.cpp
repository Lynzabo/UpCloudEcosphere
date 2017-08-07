#include "macutil.h"
#include <QNetworkInterface>
MACUtil::MACUtil()
{

}

void MACUtil::getAllMAC(QStringList &AllMACAddrs)
{
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    QString hardwareAddress;hardwareAddress.clear();
    foreach(QNetworkInterface i, list)
    {
        hardwareAddress = i.hardwareAddress();
        if(hardwareAddress.isEmpty() == false)
        {
            AllMACAddrs.append(i.hardwareAddress());
        }
    }
}

void MACUtil::getActiveMAC(QStringList &ActiveMACAddrs)
{
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    QString hardwareAddress;hardwareAddress.clear();
    foreach(QNetworkInterface i, list)
    {
        if(i.flags().operator &=(QNetworkInterface::IsUp))
        {
            hardwareAddress = i.hardwareAddress();
            if(hardwareAddress.isEmpty() == false)
            {
                ActiveMACAddrs.append(i.hardwareAddress());
            }
        }
    }
}

