/**************************************************************************
**   UpCloudEcosphere
**   Copyright (c) UpCloud C/C++ development team.
**   All rights 2016 reserved.
**   Author : dyk
**************************************************************************/

#ifndef FIOPOOL_H
#define FIOPOOL_H

#include <QObject>
#include "lsilib_global.h"
/**
 * @brief The FIOPool class 提供本地文件系统操作常用功能
 */
class LSILIBSHARED_EXPORT FIOPool : public QObject
{
public:
    explicit FIOPool(QObject *parent = 0);
    /**
     * @brief del   多线程删除文件/目录列表
     * @param posNames   文件/目录列表 可能是文件/目录的混合
     * @param asyncCount    启动线程数量
     */
    virtual void del(const QList<QString> &posNames,const quint32 asyncCount = 1) = 0;
    /**
     * @brief dir   遍历当前目录
     * @param dirName   当前目录名
     * @return  返回单前目录所有文件、文件夹
     */
    virtual QList<QString> dir(const QString &dirName) = 0;
    /**
     * @brief replace   替换文件/目录列表
     * @param posNames 文件/目录列表 可能是文件/目录的混合
     */
    virtual void replace(const QMap<QString,QString> &posNames) = 0;
    /**
     * @brief rename
     * @param posNames   文件/目录列表 可能是文件/目录的混合
     */
    virtual void rename(const QMap<QString,QString> &posNames) = 0;
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
#if 0
public slots:
    /**
     * @brief on_IOBegin    开始
     */
    virtual void on_IOBegin() = 0;
    /**
     * @brief on_IOEnd  结束
     */
    virtual void on_IOEnd() = 0;
    /**
     * @brief on_IOOneFileEnd   一个文件结束
     * @param fileName
     */
    virtual void on_IOOneFileEnd(const QString& fileName) = 0;
    /**
     * @brief on_IOProcess  进度
     * @param parsedCount
     */
    virtual void on_IOProcess(quint32 parsedCount) = 0;
    /**
     * @brief on_IOError    出错
     * @param fileName
     * @param errMsg
     */
    virtual void on_IOError(const QString& fileName, const QString &errMsg) = 0;
#endif
};

#endif // FIOPOOL_H
