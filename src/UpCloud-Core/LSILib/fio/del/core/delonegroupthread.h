/**************************************************************************
**   UpCloudEcosphere
**   Copyright (c) UpCloud C/C++ development team.
**   All rights 2016 reserved.
**   Author : dyk
**************************************************************************/

#ifndef DELONEGROUPTHREAD_H
#define DELONEGROUPTHREAD_H

#include <QtCore>

class DelOneGroupThread: public QThread
{
    Q_OBJECT
public:
    DelOneGroupThread();
    ~DelOneGroupThread();

    void init(const QList<QString> &posNames);
protected:
    void run();
signals:
    //一个文件/目录删除完成
    void evt_delOneEnd(const QString& fileName);
    //本批次删除完成
    void evt_delEnd();
    //一个文件/目录删除失败
    void evt_delOneError(const QString& fileName, const QString &errMsg);
private:
    QList<QString> m_posNames;
    QList<QString> m_files;
    QList<QString> m_dirs;
};

#endif // DELONEGROUPTHREAD_H
