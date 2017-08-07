#ifndef SERVERCONF_H
#define SERVERCONF_H

#include "base.h"
#include "baseiserverlib_global.h"
class QSettings;

class BASEISERVERLIBSHARED_EXPORT ServerConf : public QObject
{
public:
    ServerConf(QObject *parent = 0);
    /**
     * @brief getNodeMainPort   读取中心服务器到节点服务器 长连接 端口
     * @param nodeMainPort      长连接 端口
     */
    void getNodeMainPort(quint16 &nodeMainPort);

    /**
     * @brief getNodeMainTimeout    读取中心服务器到节点服务器 长连接 超时时间(s为单位)
     * @param nodeMainTimeout       长连接 超时时间
     */
    void getNodeMainTimeout(quint32 &nodeMainTimeout);

    /**
     * @brief getNodeMainBlockSize  读取中心服务器到节点服务器 长连接 传输块大小(Byte为单位)
     * @param nodeMainBlockSize     长连接 传输块大小
     */
    void getNodeMainBlockSize(quint32 &nodeMainBlockSize);

    /**
     * @brief getNOdeMainWriteTimeout 读取中心服务器到节点服务器 长连接  发送数据超时时间(ms为单位)
     * @param nodeWriteTimeout        发送数据超时时间
     */
    void getNOdeMainWriteTimeout(quint32 &nodeMainWriteTimeout);

    /**
     * @brief getNodeMainReadTimeout   读取中心服务器到节点服务器 长连接  读取数据超时时间(ms为单位)
     * @param nodeReadTimeout          读取数据超时时间
     */
    void getNodeMainReadTimeout(quint32 &nodeMainReadTimeout);

    /**
     * @brief getUiMainPort 读取中心服务器到远程UI 长连接 端口
     * @param uiMainPort    长连接 端口
     */
    void getUiMainPort(quint16 &uiMainPort);

    /**
     * @brief getUiMainTimeout  读取中心服务器到远程UI 长连接 超时时间(s为单位)
     * @param uiMainTimeout     长连接 超时时间
     */
    void getUiMainTimeout(quint32 &uiMainTimeout);

    /**
     * @brief getUiMainBlockSize    读取中心服务器到远程UI 长连接 传输块大小(Byte为单位)
     * @param uiMainBlockSize       长连接 传输块大小
     */
    void getUiMainBlockSize(quint32 &uiMainBlockSize);

    /**
     * @brief getUiMainWriteTimeout 读取中心服务器到远程UI 长连接  发送数据超时时间(ms为单位)
     * @param uiMainWriteTimeout    发送数据超时时间
     */
    void getUiMainWriteTimeout(quint32 &uiMainWriteTimeout);

    /**
     * @brief getUiMainReadTimeout  读取中心服务器到远程UI 长连接 读取数据超时时间(ms为单位)
     * @param uiMainReadTimeout     读取数据超时时间
     */
    void getUiMainReadTimeout(quint32 &uiMainReadTimeout);

    /**
     * @brief getUnStructScanTaskCycle  读取中心服务器到节点服务器 非结构化 读取扫描任务周期(ms为单位)
     * @param scanTaskCycle             扫描任务周期
     */
    void getUnStructScanTaskCycle(quint32 &scanTaskCycle);

    /**
     * @brief getStructScanTaskCycle    读取中心服务器到节点服务器 结构化 读取扫描任务周期(ms为单位)
     * @param scanTaskCycle             扫描任务周期
     */
    void getStructScanTaskCycle(quint32 &scanTaskCycle);

    /**
     * @brief getScheduleTaskScanTaskCycle  读取中心服务器到节点服务器 控制任务 读取扫描任务周期(ms为单位)
     * @param scanTaskCycle                 扫描任务周期
     */
    void getScheduleTaskScanTaskCycle(quint32 &scanTaskCycle);

    /**
     * @brief getUnstructTaskTimeout 中心服务器定时扫描非结构化任务(ms为单位)默认为5000ms
     * @param timeout 定时时间
     */
    void getUnstructTaskTimeout(quint32 &timeout);

    /**
     * @brief getStructTaskTimeout 中心服务器定时扫描结构化任务(ms为单位)默认为5000ms
     * @param timeout 定时时间
     */
    void getStructTaskTimeout(quint32 &timeout);

    /**
      * @brief getScheduleTaskTimeout 中心服务器定时扫描控制传输任务(ms为单位)默认为5000ms
      * @param timeout 定时时间
      */
    void getScheduleTaskTimeout(quint32 &timeout);

    /**
     * @brief getFtpRootPath
     * @param ftpRootPath
     */
    void getFtpRootPath(QString& ftpRootPath);

    void getFtpAddr(QString& ftpAddr);

private:
    QSettings* m_set;
};

#endif // SERVERCONF_H


