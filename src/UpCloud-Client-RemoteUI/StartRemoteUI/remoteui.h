#ifndef REMOTEUI_H
#define REMOTEUI_H

#include <QWidget>
#include <QAxBindable>
#include "remoteuiframework.h"
#include <QHBoxLayout>
class RemoteUI : public QWidget, public QAxBindable
{
    Q_OBJECT
public:
    explicit RemoteUI(QWidget *parent = 0);
    ~RemoteUI();
    //加载
    void load();
signals:

public slots:
private:
};

#endif // REMOTEUI_H
