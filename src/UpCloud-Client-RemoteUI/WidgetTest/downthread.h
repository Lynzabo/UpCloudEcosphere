#ifndef DWONTHREAD_H
#define DWONTHREAD_H

#include <QtCore>
#include "ftpclientpool.h"
class DownThread : public QThread
{
    Q_OBJECT
public:
    DownThread();
    void run();
    NetTransClient *ftpPool() const;
    void setFtpPool(NetTransClient *ftpPool);

    QMap<QString, QString> files() const;
    void setFiles(const QMap<QString, QString> &files);
signals:
    void process(const QString &file,quint64 have, quint64 total);
    void end(const QString &taskID);
    void error(const QString &taskID,const QString &src,const QString &errMsg);
    void startS();
    void subFileEnd(const QString &taskID,const QString &fileUrl,const QString &destAbst);
private slots:
    void on_process(const QString &file, quint64 have, quint64 total );
    //上传/下载等开始信号
    void on_start();
    //一个文件上传/下载完成信号
    void on_subFileEnd(const QString &taskID,const QString &fileUrl,const QString &destAbst);
    //上传/下载等结束信号
    void on_end(const QString &taskID);
    //操作出错信号
    void on_error(const QString &taskID,const QString &src,const QString &errMsg);
private:
    NetTransClient* m_ftpPool;
    QMap<QString,QString> m_files;
};

#endif // DWONTHREAD_H
