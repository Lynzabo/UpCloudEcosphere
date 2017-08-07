#include "noderequestbridgeconn.h"

NodeRequestBridgeConn::NodeRequestBridgeConn()
{
    m_pubKey.clear();
    m_priKey.clear();
    m_reqBridgeConn  = new ReqBridgeConn;
}

void NodeRequestBridgeConn::requestBridgeConn(QString &pubKeyFileName)
{
    ////[1]判断文件是否存在
    QFileInfo fileinfo(pubKeyFileName);
    if(fileinfo.exists() == false)
    {
        QString errMsg = trs("pubKeyFileName文件不存在!");
        throw errMsg;
    }
    ////[2]判断文件内容是否为空,获取公钥
    QFile pubKeyFile(pubKeyFileName);
    if(pubKeyFile.open(QIODevice::ReadOnly) == true)
    {
        //读取数据
        QTextStream in(&pubKeyFile);
        in >> m_pubKey;
        if(m_pubKey.size() <= 0)
        {
            QString errMsg = trs("公钥为空!");
            throw errMsg;
        }
    }
    else
    {
        QString errMsg = trs("打开pubKeyFile文件失败:%1!").arg(pubKeyFile.errorString());
        throw errMsg;
    }
    ////[3]获取激活的MAC地址
    QStringList activeMACAddrs;activeMACAddrs.clear();
    MACUtil::getActiveMAC(activeMACAddrs);
    if(activeMACAddrs.size() >= 1)
    {
        m_MACAddr = activeMACAddrs.at(0);
    }
    else
    {
        QString errMsg = trs("获取激活的MAC地址失败:%1!");
        throw errMsg;
    }
    ////[4]拼装请求报文实体
    //节点公钥码
    m_reqBridgeConn->PubKey = m_pubKey;
    //MAC地址
    m_reqBridgeConn->MacAddr = m_MACAddr;

}

