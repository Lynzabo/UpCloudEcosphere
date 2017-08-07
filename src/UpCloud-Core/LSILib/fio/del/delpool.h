/**************************************************************************
**   UpCloudEcosphere
**   Copyright (c) UpCloud C/C++ development team.
**   All rights 2016 reserved.
**   Author : dyk
**************************************************************************/

#ifndef DELPOOL_H
#define DELPOOL_H

#include <QObject>
#include <QMap>
class DelOneGroupThread;

class DelPool : public QObject
{
    Q_OBJECT
public:
    DelPool(QObject *parent = 0);
    ~DelPool();
    void init(const QList<QString> &posNames, const quint32 asyncCount);
    void del(void);

signals:
    //开始
    void evt_IOBegin();
    //结束
    void evt_IOEnd();
    //一个文件/目录结束
    void evt_IOOneFileEnd(const QString& fileName);
    //进度
    void evt_IOProcess(quint32 parsedCount);
    //一个文件/目录出错
    void evt_IOOneFileError(const QString& fileName, const QString &errMsg);

private slots:
    void on_IOEnd();
    void on_IOProcess(quint32 parsedCount);

    void on_IOOneGroupEnd();
    void on_IOOneFileEnd(const QString& fileName);
    void on_IOOneFileError(const QString& fileName, const QString &errMsg);
private:
    void group();
private:
    //待删除文件列表
    QList<QString> m_posNames;
    //异步删除线程数目
    quint32 m_asyncCount;
    //真实使用的线程个数
    quint32 m_realCount;
    //已经过删除的文件/目录数目
    quint32 m_hadDelCount;
    //删除线程列表
    QMap<DelOneGroupThread*, bool> m_delGroup;


};

#endif // DELPOOL_H
