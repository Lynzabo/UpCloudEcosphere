#ifndef REMOTEUIOPERAREGISTRY
#define REMOTEUIOPERAREGISTRY
#include "base.h"
#include "duplex.h"
#include "unstructoperaiserver.h"
#include "basaloperaiserver.h"
#include "structoperaiserver.h"
#include "scheduleoperaiserver.h"
//引入远程UI请求分发/监控操作
using namespace Environment::Datagram::UI_Ctrl::Opera_Type;
using namespace Environment::Datagram::Web_Serverlet::DDEditor;
/**
 *  中心服务器提供远程UI操作服务注册中心
 *  包括分发/远程监控等其他远程UI客户端操作权限控制,数据流向控制/拦截/阻塞
 */

namespace CenterRemoteOperaServiceRegistry
{
void registerOperaServices()
{
    /*----------------------------------------------------------------------操作服务注册------------*/
    //非结构化  删除任务

    FDuplexRegistryFactory::registerClass<DelUnstructTasksServlet>(Control_Module::Unstruct_delTask);
    //非结构化 查询所有列表
    FDuplexRegistryFactory::registerClass<ListUnstructTasksServlet>(Control_Module::Unstruct_listTask);
    //非结构化 查询可下发节点服务器
    FDuplexRegistryFactory::registerClass<ListSevUnstructTaskNodeSevlet>(Control_Module::Unstruct_listNodeTask);
    //非结构化 删除任务文件
    FDuplexRegistryFactory::registerClass<DelUnstructTaskFileServlet>(Control_Module::Unstruct_delTaskFile);
    //非结构化 删除任务节点服务器
    FDuplexRegistryFactory::registerClass<DelUnstructTaskNodeServlet>(Control_Module::Unstruct_delTaskNode);
    //非结构化  查看任务信息
    FDuplexRegistryFactory::registerClass<ItemUnstructTaskServlet>(Control_Module::Unstruct_itemTask);
    //非结构化 查询文件信息
    FDuplexRegistryFactory::registerClass<ListUnstructFileServlet>(Control_Module::Unstruct_listFile);
    //非结构化  添加任务
    FDuplexRegistryFactory::registerClass<AddUnstructTaskServlet>(Control_Module::Unstruct_addTask);
    //非结构化 添加任务节点服务器
    FDuplexRegistryFactory::registerClass<AddUnstructTaskNodeServlet>(Control_Module::Unstruct_addTaskNode);
    //非结构化 添加任务文件
    FDuplexRegistryFactory::registerClass<AddUnstructTaskFileServlet>(Control_Module::Unstruct_addTaskFile);
    //非结构化 修改任务信息
    FDuplexRegistryFactory::registerClass<UpdateUnstructTaskServlet>(Control_Module::Unstruct_updTask);
    //非结构化 修改任务节点服务器
    FDuplexRegistryFactory::registerClass<UpdateUnstructTaskAddrServlet>(Control_Module::Unstruct_updateTaskNode);
    //非结构化 修改任务关联状态
    FDuplexRegistryFactory::registerClass<UpdateUnstructSendStatusServlet>(Control_Module::Unstruct_updateStatus);
    //非结构化 查询任务关联状态
    FDuplexRegistryFactory::registerClass<ListUnstructSendStatusServlet>(Control_Module::Unstruct_listStatus);
    //非结构化 修改任务文件信息
    FDuplexRegistryFactory::registerClass<UpdateUnstructTaskSendFilesServlet>(Control_Module::Unstruct_updateTaskFile);
    //结构化 添加任务
    FDuplexRegistryFactory::registerClass<AddStructTaskServlet>(Control_Module::Struct_addTask);
    //结构化 修改任务
    FDuplexRegistryFactory::registerClass<UpdateStructTaskServlet>(Control_Module::Struct_updTask);
    //结构化  查询任务信息
    FDuplexRegistryFactory::registerClass<ListStructTaskServlet>(Control_Module::Struct_listTask);
    //结构化 查询指定的任务信息
    FDuplexRegistryFactory::registerClass<ItemStructTaskServlet>(Control_Module::Struct_itemTask);
    //结构化   删除任务
    FDuplexRegistryFactory::registerClass<DelStructTaskServlet>(Control_Module::Struct_delTask);
    //结构化  添加任务节点服务器
    FDuplexRegistryFactory::registerClass<AddStructSendAddrServlet>(Control_Module::Struct_addTaskNode);
    //结构化 删除任务节点服务器
    FDuplexRegistryFactory::registerClass<DelStructSendAddrServlet>(Control_Module::Struct_delTaskNode);
    //结构化  添加任务文件
    FDuplexRegistryFactory::registerClass<AddStructSendFileServlet>(Control_Module::Struct_addTaskFile);
    //结构化 删除任务文件
    FDuplexRegistryFactory::registerClass<DelStructSendFileServlet>(Control_Module::Struct_delTaskFile);
    //结构化 查询节点服务器
    FDuplexRegistryFactory::registerClass<ListStructFileServlet>(Control_Module::Struct_listFile);
    //结构化 查询任务文件
    FDuplexRegistryFactory::registerClass<ListStructAddrServlet>(Control_Module::Struct_listNodeTask);
    //结构化 修改任务节点服务器
    FDuplexRegistryFactory::registerClass<UpateStructTaskAddrServlet>(Control_Module::Struct_updateTaskAddr);
    //结构化 查询任务关联状态
    FDuplexRegistryFactory::registerClass<ListStructSendStatusServlet>(Control_Module::Struct_listStatus);
    //结构化 修改任务关联状态
    FDuplexRegistryFactory::registerClass<UpdateStructSendStatusServlet>(Control_Module::Struct_updateStatus);
    //结构化 修改任务文件信息
    FDuplexRegistryFactory::registerClass<UpdateStructTaskSendFilesServlet>(Control_Module::Struct_updateTaskFile);
    //控制传输 查询任务列表
    FDuplexRegistryFactory::registerClass<ListScheduleTaskServlet>(Control_Module::Schedule_listTask);
    //控制传输 修改任务列表
    FDuplexRegistryFactory::registerClass<UpdateScheduleTaskServlet>(Control_Module::Schedule_updateTask);
    //控制传输 查询任务信息
    FDuplexRegistryFactory::registerClass<ItemScheduleTaskServlet>(Control_Module::Schedule_itemTask);
    //控制传输 查询任务地址列表
    FDuplexRegistryFactory::registerClass<ListScheduleAddrServlet>(Control_Module::Schedule_listAddr);
    //控制传输 查询任务文件列表
    FDuplexRegistryFactory::registerClass<ListVCsAScSendFilesServlet>(Control_Module::Schedule_listFiles);
    //控制传输 修改任务节点服务器
    FDuplexRegistryFactory::registerClass<UpdateScheduleTaskAddrServlet>(Control_Module::Schedule_updateAddr);
    //控制传输 删除任务
    FDuplexRegistryFactory::registerClass<DelScheduleTaskServlet>(Control_Module::Schedule_delTask);
    //控制传输 删除任务节点服务器
    FDuplexRegistryFactory::registerClass<DelScheduleTaskAddrServlet>(Control_Module::Schedule_delAddr);
    //控制传输 删除任务文件
    FDuplexRegistryFactory::registerClass<DelScheduleTaskFilesServlet>(Control_Module::Schedule_delFiles);
    //控制传输 添加节点服务器
    FDuplexRegistryFactory::registerClass<AddScheduleTaskAddrServlet>(Control_Module::Schedule_addAddr);
    //字典管理 添加字典
    FDuplexRegistryFactory::registerClass<AddDictServlet>(Control_Module::Dict_add);
    //字典管理 查询字典
    FDuplexRegistryFactory::registerClass<ListDictServlet>(Control_Module::Dict_list);
    //字典管理 删除字典
    FDuplexRegistryFactory::registerClass<DelDictServlet>(Control_Module::Dict_del);
    //字典管理 修改字典
    FDuplexRegistryFactory::registerClass<UpdateDictServlet>(Control_Module::Dict_update);
    //服务器群组管理 添加组
    FDuplexRegistryFactory::registerClass<AddClientGroupServlet>(Control_Module::Group_addClientGroup);
    //服务器群组管理 删除组
    FDuplexRegistryFactory::registerClass<DelClientGroupServlet>(Control_Module::Group_delClientGroup);
    //服务器群组管理 查询组
    FDuplexRegistryFactory::registerClass<ListClinetGroupServlet>(Control_Module::Group_listClientGroup);
    //服务器群组管理 修改组
    FDuplexRegistryFactory::registerClass<UpdateClientGroupServlet>(Control_Module::Group_updClientGroup);
    //服务器群组节点管理 删除组内节点
    FDuplexRegistryFactory::registerClass<DelClientGroupAssocServlet>(Control_Module::Group_delGroupNode);
    //服务器群组节点管理 添加组内节点
    FDuplexRegistryFactory::registerClass<AddClientGroupAssocServlet>(Control_Module::Group_addGroupNode);
    //服务器群组节点管理 查询组内节点
    FDuplexRegistryFactory::registerClass<ListClinetGroupAssocServlet>(Control_Module::Group_listGroupNode);

    //服务器群组节点管理 修改组内节点
    FDuplexRegistryFactory::registerClass<UpdateClientGroupAssocServlet>(Control_Module::Group_updateGroupNode);
    //群组管理  改变节点服务器组的位置
    FDuplexRegistryFactory::registerClass<MoveGroupSequenceServlet>(Control_Module::Group_moveSequence);
    //群组管理 模糊查询节点服务器扩展信息
    FDuplexRegistryFactory::registerClass<ListClientExtendInfoServlet>(Control_Module::Group_listExtendInfo);

    //web jni

    //send
    FDuplexRegistryFactory::registerClass<DDEditorSendServerlet>(Opera_Type::Task_send);
    //del
    //...
    /*----------------------------------------------------------------------操作服务注册------------*/
}
}
#endif // REMOTEUIOPERAREGISTRY

