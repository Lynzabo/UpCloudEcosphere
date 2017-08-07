/**************************************************************************
**   UpCloudEcosphere
**   Copyright (c) UpCloud C/C++ development team.
**   All rights 2016 reserved.
**   Author : dyk
**************************************************************************/

#include "delpool.h"
#include <QMap>
#include "fio/del/core/delonegroupthread.h"
DelPool::DelPool(QObject *parent)
{

}

DelPool::~DelPool()
{
    m_posNames.clear();
    QList<DelOneGroupThread*> groups = m_delGroup.keys();
    qDeleteAll(groups);
    groups.clear();
    m_delGroup.clear();
}

void DelPool::init(const QList<QString> &posNames, const quint32 asyncCount)
{
    m_posNames = posNames;
    m_asyncCount = asyncCount;
    m_hadDelCount = 0;
}

void DelPool::del()
{
    //如果文件列表为空
    if(m_posNames.isEmpty())
    {
        emit evt_IOBegin();
        qDebug() << "Task start-----";
        this->on_IOProcess(0);
        this->on_IOEnd();
        return;
    }
    //运算出真实的需要用到的线程个数
    int itemCount = m_posNames.size();
    if(itemCount <= m_asyncCount)
    {
        m_realCount = itemCount;
    }
    else
    {
        m_realCount = m_asyncCount;
    }
    //根据解析文件之间的依赖性，生成指定数量的解析线程
    for(int i=0; i<m_realCount;i++)
    {
        DelOneGroupThread* delOneGroupThread = new DelOneGroupThread();
        connect(delOneGroupThread, SIGNAL(evt_delOneError(QString,QString)), this, SLOT(on_IOOneFileError(QString,QString)), Qt::QueuedConnection);
        connect(delOneGroupThread, SIGNAL(evt_delOneEnd(QString)), this, SLOT(on_IOOneFileEnd(QString)), Qt::QueuedConnection);
        connect(delOneGroupThread, SIGNAL(evt_delEnd()), this, SLOT(on_IOOneGroupEnd()), Qt::QueuedConnection);
        m_delGroup.insert(delOneGroupThread, false);
    }
    //给每个线程分配任务
    this->group();
    //开始执行删除任务

    emit evt_IOBegin();
    qDebug() << "Task start-----";

    for(int i=0; i<m_delGroup.size(); i++)
    {
        m_delGroup.keys().at(i)->start();
    }
}

//整个任务结束
void DelPool::on_IOEnd()
{
    emit evt_IOEnd();
    qDebug() << "Task end-------";
}

//整个任务的进度---已经删除的文件/目录数目
void DelPool::on_IOProcess(quint32 parsedCount)
{
    m_hadDelCount+=parsedCount;
    emit evt_IOProcess(m_hadDelCount);
    qDebug() << "parsedCount=" << m_hadDelCount;
}

//一个删除线程组结束
void DelPool::on_IOOneGroupEnd()
{
    m_delGroup[(DelOneGroupThread*)(this->sender())] = true;
    if(m_delGroup.values().contains(false) == false)
    {
        this->on_IOEnd();
    }
}

//一个删除线程组中的一个文件/目录删除结束
void DelPool::on_IOOneFileEnd(const QString &fileName)
{
    qDebug() << "DelPool::on_IOOneFileEnd" << fileName;
    emit evt_IOOneFileEnd(fileName);
    this->on_IOProcess(1);
}

//一个删除线程组中的一个文件/目录删除失败
void DelPool::on_IOOneFileError(const QString &fileName, const QString &errMsg)
{
    qDebug() << "DelPool::on_IOOneFileError" << fileName << errMsg;
    emit evt_IOOneFileError(fileName,errMsg);
    this->on_IOProcess(1);
}



//给删除线程分组分任务
void DelPool::group()
{
    //每个线程组分的文件/目录数目
    QList<int> perGroupFilesCount;

    //如果给线程数目 >= 余文件/目录数目，则每个线程分配一个即可
    if(m_asyncCount >= m_posNames.size())
    {
        for(int i=0; i<m_posNames.size(); i++)
        {
            perGroupFilesCount.append(1);
        }
    }
    else
    {
        quint32 average = m_posNames.size()/m_realCount;
        quint32 remainder = m_posNames.size()%m_realCount;
        //整除的情况
        if(remainder == 0)
        {
            for(int i=0; i<m_posNames.size(); i++)
            {
                perGroupFilesCount.append(average);
            }
        }
        //有余数的情况
        else
        {
            //如果不是完全平均分配，就对从第一个线程开始每个加1条数据直到分配完成即余数为0
            for(int i=0; i<remainder; i++)
            {
                perGroupFilesCount.append(average+1);
            }
            for(int i=0; i<(m_realCount-remainder); i++)
            {
                perGroupFilesCount.append(average);
            }

        }
    }

    //给每个线程分配文件
    QList<QString> tmpList;tmpList.clear();
    int pos = 0;
    for(int i=0; i<m_delGroup.size(); i++)
    {
        int perCount = perGroupFilesCount.at(i);
        tmpList.clear();
        tmpList = m_posNames.mid(pos,perCount);
        m_delGroup.keys().at(i)->init(tmpList);
        pos += perCount;
    }
}


