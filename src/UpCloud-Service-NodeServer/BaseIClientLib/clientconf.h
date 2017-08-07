#ifndef CLIENTCONF_H
#define CLIENTCONF_H

#include "base.h"
#include "baseiclientlib_global.h"
class QSettings;

class BASEICLIENTLIBSHARED_EXPORT ClientConf : public QObject
{
public:
    ClientConf(QObject *parent = 0);
    ~ClientConf();
public:
    /**
     * @brief getLocalhost          读取中心服务器主机地址
     * @param localhost             中心服务器主机地址
     */
    void getLocalhost(QString &localhost);

    /**
     * @brief getMainPort           读取中心服务器长连接端口
     * @param mainPort              中心服务器长连接端口
     */
    void getMainPort(quint16 &mainPort);

    /**
     * @brief getMainTimeout        读取节点服务器长连接中心服务器超时时间(ms为单位)
     * @param mainTimeout           节点服务器长连接中心服务器超时时间
     */
    void getMainTimeout(quint32 &mainTimeout);

    /**
     * @brief getBlockSize 读取节点服务器到中心服务器 长连接 传输块大小(Byte为单位)
     * @param blockSize    传输块大小
     */
    void getMainBlockSize(quint32 &blockSize);

    /**
     * @brief getMainInterval   读取节点服务器到中心服务器 长连接 设置网络连接失败多长时间重新连接(s为单位)
     * @param interval          重新连接时间
     */
    void getMainInterval(quint32 &interval);

    /**
     * @brief getMainWriteTimeout    读取节点服务器到中心服务器 长连接 发送数据超时时间(ms为单位)
     * @param writeTimeout           发送数据超时时间
     */
    void getMainWriteTimeout(quint32 &writeTimeout);

    /**
     * @brief getMainReadTimeout    读取节点服务器到中心服务器 长连接 读取数据超时时间(ms为单位)
     * @param readTimeout           读取数据超时时间
     */
    void getMainReadTimeout(quint32 &readTimeout);

    /**
     * @brief getUnStructScanTaskCycle  读取节点服务器到中心服务器 非结构化 读取扫描任务周期(ms为单位)
     * @param scanTaskCycle             扫描任务周期
     */
    void getUnStructScanTaskCycle(quint32 &scanTaskCycle);

    /**
     * @brief getStructScanTaskCycle    读取节点服务器到中心服务器 结构化 读取扫描任务周期(ms为单位)
     * @param scanTaskCycle             扫描任务周期
     */
    void getStructScanTaskCycle(quint32 &scanTaskCycle);

    /**
     * @brief getScheduleTaskScanTaskCycle  读取节点服务器到中心服务器 控制任务 读取扫描任务周期(ms为单位)
     * @param scanTaskCycle                 扫描任务周期
     */
    void getScheduleTaskScanTaskCycle(quint32 &scanTaskCycle);

    /**
     * @brief getHeartthrobTimeout 节点服务器到中心服务器 定时心跳 超时时间(ms为单位)默认为5000ms
     * @param timeout 定时时间
     */
    void getHeartthrobTimeout(quint32 &timeout);

    /**
     * @brief getUnstructTaskTimeout 中心服务器定时扫描非结构化任务(ms为单位)默认为5000ms
     * @param timeout 定时时间
     */
    void getUnstructTaskTimeout(quint32 &timeout);

    /**
     * @brief getStructDownTaskTimeout  节点服务器定时扫描结构化任务(ms为单位)默认为5000ms
     * @param timeout   定时时间
     */
    void getStructDownTaskTimeout(quint32 &timeout);
    /**
     * @brief getStructParseTaskTimeout 节点服务器定时解析结构化任务(ms为单位)默认为5000ms
     * @param timeout   定时时间
     */
    void getStructParseTaskTimeout(quint32 &timeout);
    /**
     * @brief getScheduleDownTaskTimeout    节点服务器定时扫描控制传输任务(ms为单位)默认为5000ms
     * @param timeout   定时时间
     */
    void getScheduleDownTaskTimeout(quint32 &timeout);
    /**
     * @brief getScheduleExecTaskTimeout    节点服务器定时执行控制传输任务(ms为单位)默认为5000ms
     * @param timeout   定时时间
     */
    void getScheduleExecTaskTimeout(quint32 &timeout);
private:
    QSettings* m_set;
};

#endif // CLIENTCONF_H


