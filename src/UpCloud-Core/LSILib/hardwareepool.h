/**************************************************************************
**   UpCloudEcosphere
**   Copyright (c) UpCloud C/C++ development team.
**   All rights 2016 reserved.
**   Author : dyk
**************************************************************************/

#ifndef HARDWAREEPOOL_H
#define HARDWAREEPOOL_H

#include <QObject>
/**
 * @brief The HardwareEPool class   提供本地硬件操作功能
 * 例如提取CPU、内存占有,指定进程下栈区情况/线程数量等硬件相关指标,强制结束进程等
 */
class HardwareEPool : public QObject
{
    Q_OBJECT
public:
    explicit HardwareEPool(QObject *parent = 0);

signals:

public slots:
};

#endif // HARDWAREEPOOL_H
