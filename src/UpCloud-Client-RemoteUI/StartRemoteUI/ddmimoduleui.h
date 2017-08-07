/**************************************************************************
**   UpCloudEcosphere
**   Copyright (c) UpCloud C/C++ development team.
**   All rights 2016 reserved.
**   Author : Lynzabo
**************************************************************************/

#ifndef DDMIMODULEUI_H
#define DDMIMODULEUI_H

#include "ui_ddmimoduleui.h"
#include "modules/common/funcsmenu.h"
#include "modules/common/uihelper.h"
/**
 * @brief The DDMIStackWidget class 数据分发模块
 */
class DDMIModuleUI : public QWidget, private Ui::DDMIModuleUI
{
    Q_OBJECT

public:
    explicit DDMIModuleUI(QWidget *parent = 0);
protected:
    virtual void showEvent(QShowEvent *);
private:
    /**
     * @brief initWindow    初始化窗口基本数据
     */
    void initWindow();
private slots:
    /**
     * @brief doFuncClick   功能区按钮点击
     * @param btnname
     */
    void doFuncClick(const QString & btnname);
private:
    //功能按钮信号处理映射器
    QSignalMapper *signalMapper;
    QButtonGroup *bg_funcs;
    FuncsMenu *funcs_menu;
};

#endif // DDMIMODULEUI_H
