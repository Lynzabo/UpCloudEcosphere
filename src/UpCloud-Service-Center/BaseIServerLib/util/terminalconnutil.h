#ifndef TERMINALCONNUTIL_H
#define TERMINALCONNUTIL_H

#include <QtCore>
#include <QTcpSocket>
#include "base.h"
#include "../baseiserverlib_global.h"

class  BASEISERVERLIBSHARED_EXPORT TerminalConnUtil
{
    SINGLETON(TerminalConnUtil)
public:
    /**
     * @brief insertTerminal    添加终端
     * @param terSock
     * @param terUUID
     * 根据固定码可以判断客户端类型
     */
    void insertTerminal(const QTcpSocket* terSock, const quint64 &terUUID);
    /**
     * @brief delTerminal   删除指定终端
     * @param terSock
     */
    void delTerminal(const QTcpSocket *&terSock);
    /**
     * @brief listTerminal  输出节点服务器列表
     * @param equipMainType 设备主类型码
     * @return
     */
    const QMap<const QTcpSocket *, quint64> &listTerminal(const quint8 &equipMainType) const;

private:
    ////已建立长连接客户端
    //在线桌面客户端列表
    QMap<const QTcpSocket*,quint64> desktopRemoteUIClients;
    //在线J2EE Web客户端列表
    QMap<const QTcpSocket*,quint64> j2EERemoteUIClients;
    //在线节点服务器列表
    QMap<const QTcpSocket*,quint64> desktopNodeUIClients;
    //添加删除锁
    QMutex lock;
};

#endif // TERMINALCONNUTIL_H
