#ifndef REMOTEUIWINDOW_H
#define REMOTEUIWINDOW_H

#include <QWidget>
#include <QAxBindable>
#include "remoteuiframework.h"

class RemoteUIWindow : public QWidget, public QAxBindable
{
    Q_OBJECT
public:
    explicit RemoteUIWindow(QWidget *parent = 0);

signals:

public slots:
private:
    RemoteUIFrameWork *frameRemoteUI;

    // QWidget interface
protected:
    virtual void showEvent(QShowEvent *);
};

#endif // REMOTEUIWINDOW_H
