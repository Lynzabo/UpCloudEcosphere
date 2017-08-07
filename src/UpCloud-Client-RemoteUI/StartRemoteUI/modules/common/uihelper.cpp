#include "uihelper.h"
#include "loading.h"
UIHelper::UIHelper(QObject *parent) : QObject(parent)
{

}

void UIHelper::OpenInSelf(QWidget *curWindow, QWidget *openWidget, const QString stackName)
{
    showLoading(curWindow,tr("正在加载页面"));
    QStackedWidget *sw_content = 0;
    QObject *parent = curWindow->parent();
    if(!parent)
    {
        parent = curWindow->findChild<QStackedWidget *>(stackName);
    }
    if(parent ->inherits("QStackedWidget") && parent->objectName() == stackName)
    {
        sw_content = qobject_cast<QStackedWidget *>(parent);
        if(sw_content)
        {
            QString openWidgetName = openWidget->objectName();
            QWidget *wid = sw_content->findChild<QWidget *>(openWidgetName,Qt::FindDirectChildrenOnly);
            //如果已经包含这个窗体
            if(wid)
            {
                int index = -1;
                QWidget *childWidget = 0;
                for(int i = 0;i<sw_content->count();i++)
                {
                    childWidget = sw_content->widget(i);
                    QString ChildwidName = childWidget->objectName();
                    if((!ChildwidName.isEmpty())&&(ChildwidName == openWidgetName))
                    {
                        index = i;
                        break;
                    }
                }
                if(index < 0 || !childWidget)
                {
                    goto add;
                }
                else
                {
                    sw_content->removeWidget(childWidget);
                    goto add;
                }
            }
            else
            {
add:
                //sw_content->setCurrentIndex(sw_content->size()-1);
                sw_content->addWidget(openWidget);
                sw_content->setCurrentWidget(openWidget);
                hideLoading(curWindow);
            }
        }
    }
    else
    {
        ShowMessageBoxError(tr("打开失败"));
    }
}

void UIHelper::OpenInTop(QWidget *curWindow, QWidget *openWidget, const QString stackName)
{
    showLoading(curWindow,tr("正在加载页面"));
    QStackedWidget *sw_content = 0;
    QObject *obj = curWindow->findChild<QStackedWidget *>(stackName);
    if(obj!=NULL && obj ->inherits("QStackedWidget") && obj->objectName() == stackName)
    {
        sw_content = qobject_cast<QStackedWidget *>(obj);
        if(sw_content)
        {
            QString openWidgetName = openWidget->objectName();
            QWidget *wid = sw_content->findChild<QWidget *>(openWidgetName,Qt::FindDirectChildrenOnly);
            //如果已经包含这个窗体
            if(wid)
            {
                int index = -1;
                QWidget *childWidget = 0;
                for(int i = 0;i<sw_content->count();i++)
                {
                    childWidget = sw_content->widget(i);
                    QString ChildwidName = childWidget->objectName();
                    if((!ChildwidName.isEmpty())&&(ChildwidName == openWidgetName))
                    {
                        index = i;
                        break;
                    }
                }
                if(index < 0 || !childWidget)
                {
                    goto add;
                }
                else
                {
                    sw_content->removeWidget(childWidget);
                    goto add;
                }
            }
            else
            {
add:
                //sw_content->setCurrentIndex(sw_content->size()-1);
                sw_content->addWidget(openWidget);
                sw_content->setCurrentWidget(openWidget);
                hideLoading(curWindow);
            }
        }
    }
    else
    {
        ShowMessageBoxError(tr("打开失败"));
    }
}

void UIHelper::showLoading(QWidget *curWindow, const QString &msg)
{
    Loading *loading = curWindow->findChild<Loading *>(QString("RemoteUISystemLoadingUI"));
    if(!loading)
    {
        loading  = new Loading(curWindow);
        loading->setObjectName(QString("RemoteUISystemLoadingUI"));
        loading->hide();
        loading->resize(curWindow->size());
    }
    loading->setMsg(msg);
    loading->show();
}

void UIHelper::hideLoading(QWidget *curWindow)
{
    Loading *loading = curWindow->findChild<Loading *>(QString("RemoteUISystemLoadingUI"));
    if(loading)
        loading->close();
}

