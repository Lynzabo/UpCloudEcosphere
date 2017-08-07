/**************************************************************************
**   UpCloudEcosphere
**   Copyright (c) UpCloud C/C++ development team.
**   All rights 2016 reserved.
**   Author : Lynzabo
**************************************************************************/

#ifndef OMMIMODULEUI_H
#define OMMIMODULEUI_H

#include "ui_ommimoduleui.h"
/**
 * @brief The OMMIModuleUI class 运维监控模块
 */
class OMMIModuleUI : public QWidget, private Ui::OMMIModuleUI
{
    Q_OBJECT

public:
    explicit OMMIModuleUI(QWidget *parent = 0);
};

#endif // OMMIMODULEUI_H
