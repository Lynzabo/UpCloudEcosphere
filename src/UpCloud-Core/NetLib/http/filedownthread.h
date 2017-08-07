#ifndef FILEDOWNTHREAD_H
#define FILEDOWNTHREAD_H
#include <QtCore>
#include <QtNetwork>
#include "fileblockdownloadthread.h"
class FileDownThread : public QThread
{
    Q_OBJECT
public:
    FileDownThread(const QString &index);
    ~FileDownThread();
    void SetDownloadProp(const QString &url, const QString &abstPath, const int &subAyncsSize=5);
    //要下载的文件大小
    qint64 GetFileSize(QUrl url);

    QString getF_Url();

signals:
    //当前文件下载完毕信号
    void FileDownloadFinish(const QString &fKey);
    //下载文件失败信号
    void FileDownloadError(const QString &fKey,const QString &errorStr);
    //下载进度
    void process(const QString &fileUrl,const quint64 &haveDoneBytes,const quint64 &totalBytes);
protected:
    void run();
private slots:
    void writeIOBytes(int size);
    void SubBlockDownloadError(const int &index, const QString &errorStr);
    void SubPartFinished(int index);
    void WriteBlocks(const QByteArray &buffer, const quint64 &pos);
private:
    //线程下载主键
    QString f_Key;
    //下载文件URL
    QString f_Url;
    //绝对路径
    QString f_AbstPath;
    //下载文件URL
    QUrl f_URL;
    //当前文件下载线程数
    int f_SubAyncsSize;
    //要下载的文件大小
    quint64 f_FileSize;
    //多线程已接收串长度
    quint64 f_ReceiveSize;
    //完成下载的线程数
    int f_FinishedNum;
    //要下载的文件对象
    QFile *f_File;
    QVector<FileBlockDownloadThread*> threadsVector;
    //锁定当前文件写入锁
    QReadWriteLock *lock;
    QReadWriteLock *lockSize;
};

#endif // FILEDOWNTHREAD_H
