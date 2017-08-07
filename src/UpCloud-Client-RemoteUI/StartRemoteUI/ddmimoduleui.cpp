/**************************************************************************
**   UpCloudEcosphere
**   Copyright (c) UpCloud C/C++ development team.
**   All rights 2016 reserved.
**   Author : Lynzabo
**************************************************************************/

#include "ddmimoduleui.h"
#include "modules/ddmi/unstructUI/dirunstructwidget.h"
#include "modules/ddmi/unstructUI/editunstructwidget.h"
#include "modules/ddmi/structUI/dirstructwidget.h"
#include "modules/ddmi/structUI/editstructwidget.h"
#include "modules/ddmi/scheduleUI/dirschedulewidget.h"
#include "modules/ddmi/scheduleUI/editschedulewidget.h"
#include "modules/basal/nsgroupUI/dirnodesgroupwidget.h"
#include "modules/basal/dictUI/dirdictwidget.h"

DDMIModuleUI::DDMIModuleUI(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    initWindow();
}

void DDMIModuleUI::showEvent(QShowEvent *)
{
    //设置默认单击非结构化管理
    emit
        this->btn_unstruct->click();
}

void DDMIModuleUI::initWindow()
{
    //功能更多菜单
    signalMapper = new QSignalMapper(this);
    funcs_menu = new FuncsMenu(this);
    this->btn_sysmanagement->setMenu(funcs_menu);
//    connect(funcs_menu,SIGNAL(evt_triggedGroup()),this,SLOT(on_clickedGroup()));
//    connect(funcs_menu,SIGNAL(evt_triggedDict()),this,SLOT(on_clickedDict()));

    connect(funcs_menu->action_sgroup,SIGNAL(triggered(bool)),signalMapper,SLOT(map()));
    signalMapper->setMapping (funcs_menu->action_sgroup, funcs_menu->action_sgroup->objectName());
    connect(funcs_menu->action_sdict,SIGNAL(triggered(bool)),signalMapper,SLOT(map()));
    signalMapper->setMapping (funcs_menu->action_sdict, funcs_menu->action_sdict->objectName());

    connect(this->btn_unstruct, SIGNAL(clicked()), signalMapper, SLOT(map ()));
    signalMapper->setMapping (this->btn_unstruct, this->btn_unstruct->objectName());
    connect(this->btn_struct, SIGNAL(clicked()), signalMapper, SLOT(map ()));
    signalMapper->setMapping (this->btn_struct, this->btn_struct->objectName());
    connect(this->btn_schedule, SIGNAL(clicked()), signalMapper, SLOT(map ()));
    signalMapper->setMapping (this->btn_schedule, this->btn_schedule->objectName());

    connect(signalMapper, SIGNAL(mapped (const QString &)), this, SLOT(doFuncClick(const QString &)));
    //功能单选设置
    bg_funcs = new QButtonGroup(this);
    bg_funcs->addButton(this->btn_unstruct);
    this->btn_unstruct->setCheckable(true);
    bg_funcs->addButton(this->btn_struct);
    this->btn_struct->setCheckable(true);
    bg_funcs->addButton(this->btn_schedule);
    this->btn_schedule->setCheckable(true);
    bg_funcs->addButton(this->btn_sysmanagement);
    this->btn_sysmanagement->setCheckable(true);
}

void DDMIModuleUI::doFuncClick(const QString &btnname)
{
    if(btnname.isEmpty())
    {
        return;
    }
    //非结构化管理
    if(btnname==this->btn_unstruct->objectName())
    {
        //打开非结构化任务列表
        UIHelper::OpenInTop(this,new DirUnstructWidget(this));
    }
    //结构化管理
    if(btnname==this->btn_struct->objectName())
    {
        //打开非结构化任务列表
        UIHelper::OpenInTop(this,new DirStructWidget(this));
    }
    //远控管理
    if(btnname==this->btn_schedule->objectName())
    {
        //打开远控任务列表
        UIHelper::OpenInTop(this,new DirScheduleWidget(this));
    }
    //群组管理
    if(btnname=="a_nodergroup")
    {
        this->btn_sysmanagement->setChecked(true);
        UIHelper::OpenInTop(this,new DIRNodesGroupWidget(this));
    }
    //字典维护
    if(btnname=="a_dict")
    {
        this->btn_sysmanagement->setChecked(true);
        UIHelper::OpenInTop(this,new DirDictWidget(this));
    }

    //非结构化详情
    if(btnname==QStringLiteral("btn_unstructTaskDetail"))
    {
        this->sw_content->setCurrentIndex(0);
    }
    //结构化详情
    if(btnname==QStringLiteral("btn_structTaskDetail"))
    {
        this->sw_content->setCurrentIndex(1);
    }
}

