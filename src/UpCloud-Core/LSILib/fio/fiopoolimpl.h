/**************************************************************************
**   UpCloudEcosphere
**   Copyright (c) UpCloud C/C++ development team.
**   All rights 2016 reserved.
**   Author : dyk
**************************************************************************/

#ifndef FIOPOOLIMPL_H
#define FIOPOOLIMPL_H

#include "fiopool.h"
#include "lsilib_global.h"
class DelPool;

class LSILIBSHARED_EXPORT FIOPoolImpl : public FIOPool
{
    Q_OBJECT
public:
    FIOPoolImpl();
    ~FIOPoolImpl();
    virtual void del(const QList<QString> &posNames,const quint32 asyncCount = 1);
    virtual QList<QString> dir(const QString &dirName);
    virtual void replace(const QMap<QString,QString> &posNames);
    virtual void rename(const QMap<QString,QString> &posNames);
signals:
    //开始
    void evt_IOBegin();
    //结束
    void evt_IOEnd();
    //一个文件结束
    void evt_IOOneFileEnd(const QString& fileName);
    //进度
    void evt_IOProcess(quint32 parsedCount);
    //出错
    void evt_IOOneFileError(const QString& fileName, const QString &errMsg);
private:
    DelPool* m_delPool;
};

#endif // FIOPOOLIMPL_H
