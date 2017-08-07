#ifndef FTPCOMMONMANAGER_H
#define FTPCOMMONMANAGER_H

/**
 * @brief The FtpCommonManager class 处理ftp常用操作
 *
 * 1.List       列出当前目录下的所有子目录及文件
 * 2.Cd         更改当前所在目录
 * 3.Rename     重命名文件/目录
 * 4.Remove     删除文件
 * 5.Rmdir      删除目录
 * 6.Mkdir      创建目录
 */

#include <QtCore>
#include "core/qftp.h"
#include "ftpmeta.h"
#include "netlib_global.h"

struct NETLIBSHARED_EXPORT list_info
{
    bool isDir ;
    QString name;
    int permissions;
    QString owner;
    QString group;
    qint64 size;
    QDateTime lastModified;
    QDateTime lastRead;
};

class NETLIBSHARED_EXPORT FtpCommonManager : public QObject
{
    Q_OBJECT
public:
    explicit FtpCommonManager();
    ~FtpCommonManager();

    void init(FtpMeta *_meta);
public:
    /**
     * @brief list
     * @param dir       目录名
     * @param listInfo  目录信息
     */
    void list(const QString &dir, QList<struct list_info> *listInfo);
    void cd(const QString &dir);
    void rename(const QString &oldname, const QString &newname);
    void remove(const QString &file);
    void rmdir(const QString &dir);
    void mkdir(const QString &dir);
    void size(const QString &fileUrl, qint64* fileSize);
signals:
    //操作开始信号
    void start();
    //操作进度信号
    void process(const QString &objectName,const quint64 &haveDoneBytes,const quint64 &totalBytes);
    //操作结束信号
    void end();
    //操作出错信号
    void error(const QString &src, const QString &errMsg);
private slots:
    void hander_listInfo(const QUrlInfo &urlInfo);
    void hander_commandFinished(int id, bool backSatus);
    void hander_process(qint64 haveDoneBytes, qint64 totalBytes);    
public slots:
    void hander_rawCommandReply(int tmp, const QString& output);
private:    
    //清空上次的数据
    void clear();
    //连接服务器
    void connect();
private:
    QFtp *m_qftp;
    //ftp服务信息
    FtpMeta *m_meta;
    //存储目录/文件信息
    QList<struct list_info>* m_listInfo;
    //存储文件大小
    qint64* m_fileSize;
    //存储操作对象名（目录名/文件名）
    QString m_objectName;   
};

#endif // FTPCOMMONMANAGER_H
