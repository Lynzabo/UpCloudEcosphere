#ifndef FILEBLOCKDOWNLOADTHREAD_H
#define FILEBLOCKDOWNLOADTHREAD_H

#include <QtCore>
#include <QtNetwork>
class FileBlockDownloadThread : public QThread
{
    Q_OBJECT
public:
    /**
     * @brief DownloadBlockThread
     * @param index 当前线程索引
     * @param parent
     */
    FileBlockDownloadThread(int index);
    ~FileBlockDownloadThread();
    void SetDownloadProp(const QUrl &url, QFile *file,
        quint64 startPoint=0, quint64 endPoint=-1);
signals:
    void readIOBytes(int size);
    void blockDownloadFinished(int index);
    //下载文件块失败信号
    void BlockDownloadError(const int &index,const QString &errorStr);
    void ReadBlocks(const QByteArray &buffer,const quint64 &pos);
protected:
    void run();
private slots:
    //下载文件块
    void downloadReadyRead();
    void replyFinished();
private:
    //要下载文件
    QFile *m_File;
    //要下载文件名
    QString m_FileName;
    //本次下载长度
    quint64 m_HaveDoneBytes;
    //要下载的开始位置
    quint64 m_StartPoint;
    //要下载的结束位置
    quint64 m_EndPoint;
    //下载文件URL
    QUrl m_Url;
    QNetworkAccessManager *_manager;
    QNetworkReply *reply;
    const int m_Index;
};

#endif // FILEBLOCKDOWNLOADTHREAD_H
