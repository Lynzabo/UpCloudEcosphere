/**
 * ━━━━━━神兽出没━━━━━━
 * 　　 　┏┓　　　┏┓
 * 　  ┏┛┻━━━┛┻┓
 * 　　┃　　　　　　　┃
 * 　　┃　　　━　　　┃
 * 　　┃　┳┛　┗┳　┃
 * 　　┃　　　　　　　┃
 * 　　┃　　　┻　　　┃
 * 　　┃　　　　　　　┃
 * 　　┗━┓　　　┏━┛
 * 　　　　┃　　　┃神兽保佑, 永无BUG!
 * 　　　　┃　　　┃Code is far away from bug with the animal protecting
 * 　　　　┃　　　┗━━━┓
 * 　　　　┃　　　　　　　┣┓
 * 　　　　┃　　　　　　　┏┛
 * 　　　　┗┓┓┏━┳┓┏┛
 * 　　　　　┃┫┫　┃┫┫
 * 　　　　　┗┻┛　┗┻┛
 * ━━━━━━感觉萌萌哒━━━━━━
 * Module Desc: 生态圈常量配置
 * User: Lynzabo || lzb_178@163.com
 * Date: 2015/7/21
 * Time: 14:27
 */
#ifndef CONSTANT
#define CONSTANT
#include <QtCore>
#include "unicode.h"
/**
 *  定义系统常量
 */
namespace Environment
{
    /////////////////////////////////////////////////////////////////网络begin
    //TCP服务端绑定端口打开监听状态
    namespace Server_Net_Listen
    {
        //监听成功
        const bool LISTEN_SUCCESS = true;
        //监听失败
        const bool LISTEN_FAIL = false;
    }
    //网络连接状态
    namespace Net_Conn_State
    {
        //网络连接成功
        const bool CONN_SUCCESS = true;
        //网络连接失败
        const bool CONN_FAIL = false;
    }
    namespace Net_Transfer_Rules
    {
        //长连接握手成功标识符
        const QString HANDSHAKE = "621229FA-7117-066D-F3B5-0814A9FF5D81";
    }
    //网络传输发送端主设备类型
    namespace Net_Equip_MainType
    {
        //远程UI客户端
        const quint8 DESKTOP_NODER = 0x1;
        //桌面远程UI客户端
        const quint8 DESKTOP_REMOTEUI = 0x2;
        //J2EE-WEB接口远程UI客户端
        const quint8 J2EE_REMOTEUI = 0x3;
    }
    //网络传输发送端设备副类型
    namespace EquipSubType
    {
        //远程UI客户端
        namespace DESKTOP_NODER
        {

        }
        //桌面远程UI客户端
        namespace DESKTOP_REMOTEUI
        {
            //桌面版远程UI客户端
            const quint8 DESKTOP_REMOTEUI = 0x1;
            //OCX版远程UI客户端
            const quint8 OCX_REMOTEUI = 0x2;
            //NPAPI版远程UI客户端
            const quint8 NPAPI_REMOTEUI = 0x3;
            //OCX版查看下发服务任务状态远程UI客户端插件
            const quint8 OCX_SEETASKINFO_PLUGIN = 0x4;
            //NPAPI版查看下发服务任务状态远程UI客户端插件
            const quint8 NPAPI_SEETASKINFO_PLUGIN = 0x5;
        }
        //J2EE-WEB接口远程UI客户端
        namespace J2EE_REMOTEUI
        {
            //数据分发服务远程UI客户端JNI插件
            const quint8 DDMI_JNI_REMOTEUI = 0x1;
            //运维监控服务远程UI客户端JNI插件
            const quint8 OMMI_JNI_REMOTEUI = 0x2;
            //获取节点服务器基础指标远程UI客户端JNI插件
            const quint8 BASICENV_JNI_REMOTEUI = 0x3;
        }
    }
    //网络传输发送端设备状态
    namespace EquipState
    {
        //不可用
        const quint8 DISABLED = 0x1;
        //可用
        const quint8 USABLE = 0x2;
    }
    /////////////////////////////////////////////////////////////////网络end
    /////////////////////////////////////////////////////////////////文件传输类型begin
    //
    namespace Files_Src_Type
    {
        //WEB插件传输文件标示
        const quint8 WEB = 0x1;
        //远程UI客户端传输文件标示
        const quint8 RemoteUI = 0x2;
    }
    /////////////////////////////////////////////////////////////////文件传输类型end

    /////////////////////////////////////////////////////////////////全双工交互begin
    namespace Duplex_Interaction
    {
        //请求地址定义,下层namespace中URL必须唯一,不能重复
        namespace Data_Authority
        {
            const quint8 _0 = 0x0;const QString _0_DESC_Success = trs("成功");
            const quint8 _1 = 0x1;const QString _1_DESC_Unauthorized = trs("未授权访问地址 ");
            const quint8 _2 = 0x2;const QString _2_DESC_AddrIsInvalid = trs("访问地址无效");
            const quint8 _3 = 0x3;const QString _3_DESC_SeiviceIsNull = trs("未找到后台服务 ");
            const quint8 _4 = 0x4;const QString _4_DESC_DatabaseError = trs("操作数据库失败 ");
            const quint8 _5 = 0x5;const QString _5_DESC_ParamParseError = trs("解析参数列表失败");
            const quint8 _6 = 0x6;const QString _6_DESC_NoderIsNull = trs("没有可下发的服务节点");
            const quint8 _7 = 0x7;const QString _7_DESC_ParamsHasNullValue = trs("参数为空");
            const quint8 _8 = 0x8;const QString _8_DESC_ParseDataError = trs("解析返回数据失败");
            const quint8 _9 = 0x9;const QString _9_DESC_RecordIsExsit = trs("记录已经存在");
            const quint8 _10 =0x10;const QString _10_DESC_RecordEmpty = trs("没有记录");
        }
    }
    /////////////////////////////////////////////////////////////////全双工交互end

    /////////////////////////////////////////////////////////////////客户端交互begin
    //包括远程UI客户端,远程UI Web插件,节点服务器
    namespace Terminal_Now_State
    {
        //在线状态
        const quint8 ON_LINE = 0x1;
        //离线状态
        const quint8 OFF_LINE = 0x2;
        //挂起状态  预留字段
        const quint8 SUSPEND = 0x3;
    }
    /////////////////////////////////////////////////////////////////客户端交互end


    /////////////////////////////////////////////////////////////////数据库begin
    //操作数据库事务状态
    namespace Db_Transaction_State
    {
        //操作成功
        const bool TRANS_SUCCESS = true;
        //操作失败
        const bool TRANS_FAIL = false;
    }
    /////////////////////////////////////////////////////////////////数据库end

    /////////////////////////////////////////////////////////////////串口通讯begin
    namespace Serial {
        //串口通讯数据类型定义
        namespace DataType {
            //请求获取GPS模块数据
            const quint8 GPS = 0x1;
            //请求获取GPS模块数据
            const quint8 TemHum = 0x2;
            //同步服务端时间
            const quint8 SyschronizedTime = 0x3;
            //获取设备机器码
            const quint8 MachineUUID = 0x4;
            //心跳
            const quint8 Heartthrob = 0x5;
        }
    }
    /////////////////////////////////////////////////////////////////串口通讯end

    /////////////////////////////////////////////////////////////////处理任务状态begin
    /// 其中包含中心服务器分发和监控时候状态,节点服务器分发和监控时候状态,远程UI运行状态等
    namespace Task_Status
    {
        //中心服务端状态定义
        namespace Center
        {
            //非结构化任务状态
            namespace Unstru
            {
                //任务表状态
                namespace Task_State
                {
                    //废弃
                    const quint8 DISCARD = 0x0;
                    //可用
                    const quint8 USABLE = 0x1;                    
                    //准备下发
                    const quint8 PRESEND = 0x2;
                    //正在下发
                    const quint8 SENDING = 0x3;
                    //目标地址为空
                    const quint8 ADDRISNULL = 0x4;
                    //下发出错
                    const quint8 SENDERROR = 0x5;
                    //下发成功
                    const quint8 SENDSUCCESS = 0x6;
                    //下载出错
                    const quint8 DOWNERROR = 0x7;
                    //下载成功
                    const quint8 DOWNSUCCESS = 0x8;
                    //任务处理失败
                    const quint8 TASKERROR = 0x9;
                    //任务处理成功
                    const quint8 TASKSUCCESS = 0xA;
                    //任务处于暂停中
                    const quint8 PAUSE= 0xB;
                    //任务处于缓存中
                    const quint8 CACHEING = 0xC;

                }
                //关联状态
                namespace SendStatus_State
                {
                    //废弃
                    const quint8 DISCARD = 0x0;
                    //可用
                    const quint8 USABLE = 0x1;
                    //准备下发
                    const quint8 PRESEND = 0x2;
                    //正在下发
                    const quint8 SENDING = 0x3;
                    //下发出错
                    const quint8 SENDERROR = 0x4;
                    //下发成功
                    const quint8 SENDSUCCESS = 0x5;                    
                    //下载出错
                    const quint8 DOWNERROR = 0x6;
                    //下载成功
                    const quint8 DOWNSUCCESS = 0x7;
                }
                namespace Task_Strategy
                {

                }
            }
            //结构化任务状态
            namespace Stru
            {
                //任务表状态
                namespace Task_State
                {
                    //废弃
                    const quint8 DISCARD = 0x0;
                    //可用
                    const quint8 USABLE = 0x1;
                    //准备下发
                    const quint8 PRESEND = 0x2;
                    //正在下发
                    const quint8 SENDING = 0x3;
                    //目标地址为空
                    const quint8 ADDRISNULL = 0x4;
                    //下发出错
                    const quint8 SENDERROR = 0x5;
                    //下发成功
                    const quint8 SENDSUCCESS = 0x6;
                    //下载出错
                    const quint8 DOWNERROR = 0x7;
                    //下载成功
                    const quint8 DOWNSUCCESS = 0x8;
                    //解析失败
                    const quint8 PARSEERROR = 0x9;
                    //解析成功
                    const quint8 PARSESUCCESS = 0xA;
                    //任务处理失败
                    const quint8 TASKERROR = 0xB;
                    //任务处理成功
                    const quint8 TASKSUCCESS = 0xC;
                    //任务处于暂停中
                    const quint8 PAUSE= 0xD;
                    //任务处于缓存中
                    const quint8 CACHEING = 0xE;
                }
                //关联状态
                namespace SendStatus_State
                {
                    //废弃
                    const quint8 DISCARD = 0x0;
                    //可用
                    const quint8 USABLE = 0x1;
                    //准备下发
                    const quint8 PRESEND = 0x2;
                    //正在下发
                    const quint8 SENDING = 0x3;
                    //下发出错
                    const quint8 SENDERROR = 0x4;
                    //下发成功
                    const quint8 SENDSUCCESS = 0x5;
                    //下载出错
                    const quint8 DOWNERROR = 0x6;
                    //下载成功
                    const quint8 DOWNSUCCESS = 0x7;
                    //解析失败
                    const quint8 PARSEERROR = 0x8;
                    //解析成功
                    const quint8 PARSESUCCESS = 0x9;
                }                
            }
            //控制传输任务状态
            namespace Sche
            {
                //任务表状态
                namespace Task_State
                {
                    //废弃
                    const quint8 DISCARD = 0x0;
                    //可用
                    const quint8 USABLE = 0x1;
                    //准备下发
                    const quint8 PRESEND = 0x2;
                    //正在下发
                    const quint8 SENDING = 0x3;
                    //目标地址为空
                    const quint8 ADDRISNULL = 0x4;
                    //下发出错
                    const quint8 SENDERROR = 0x5;
                    //下发成功
                    const quint8 SENDSUCCESS = 0x6;
                    //下载出错
                    const quint8 DOWNERROR = 0x7;
                    //下载成功
                    const quint8 DOWNSUCCESS = 0x8;
                    //执行失败
                    const quint8 EXECERROR = 0x9;
                    //执行成功
                    const quint8 EXECSUCCESS = 0xA;
                    //任务处理失败
                    const quint8 TASKERROR = 0xB;
                    //任务处理成功
                    const quint8 TASKSUCCESS = 0xC;
                    //任务处于暂停中
                    const quint8 PAUSE= 0xD;
                    //任务处于缓存中
                    const quint8 CACHEING = 0xE;
                }
                //地址表状态
                namespace SendAddr_State
                {
                    //废弃
                    const quint8 DISCARD = 0x0;
                    //可用
                    const quint8 USABLE = 0x1;
                    //准备下发
                    const quint8 PRESEND = 0x2;
                    //正在下发
                    const quint8 SENDING = 0x3;
                    //下发出错
                    const quint8 SENDERROR = 0x4;
                    //下发成功
                    const quint8 SENDSUCCESS = 0x5;
                    //下载出错
                    const quint8 DOWNERROR = 0x6;
                    //下载成功
                    const quint8 DOWNSUCCESS = 0x7;
                    //执行失败
                    const quint8 EXECERROR = 0x8;
                    //执行成功
                    const quint8 EXECSUCCESS = 0x9;
                }
                namespace SendFile_State
                {
                    //废弃
                    const quint8 DISCARD = 0x0;
                    //可用
                    const quint8 USABLE = 0x1;
                    //准备下发
                    const quint8 PRESEND = 0x2;
                    //正在下发
                    const quint8 SENDING = 0x3;
                    //下发出错
                    const quint8 SENDERROR = 0x4;
                    //下发成功
                    const quint8 SENDSUCCESS = 0x5;
                    //下载出错
                    const quint8 DOWNERROR = 0x6;
                    //下载成功
                    const quint8 DOWNSUCCESS = 0x7;
                    //执行失败
                    const quint8 EXECERROR = 0x8;
                    //执行成功
                    const quint8 EXECSUCCESS = 0x9;
                }
            }
        }

        //节点服务端状态定义
        namespace Noder
        {
            //非结构化任务状态
            namespace Unstru
            {
                //任务表状态
                namespace Task_State
                {
                    //废弃
                    const quint8 DISCARD = 0x0;
                    //可用
                    const quint8 USABLE = 0x1;
                    //正在下载
                    const quint8 DOWNING = 0x2;
                    //下载出错
                    const quint8 DOWNERROR = 0x3;
                    //下载成功
                    const quint8 DOWNSUCCESS = 0x4;
                    //任务处理失败
                    const quint8 TASKERROR = 0x5;
                    //任务处理成功
                    const quint8 TASKSUCCESS = 0x6;

                }
                //下发文件处理表状态
                namespace SendFiles_State
                {
                    //废弃
                    const quint8 DISCARD = 0x0;
                    //可用
                    const quint8 USABLE = 0x1;
                    //正在下载
                    const quint8 DOWNING = 0x2;
                    //下载出错
                    const quint8 DOWNERROR = 0x3;
                    //下载成功
                    const quint8 DOWNSUCCESS = 0x4;
                 }
            }
            //结构化任务状态
            namespace Stru
            {
                //任务表状态
                namespace Task_State
                {
                    //废弃
                    const quint8 DISCARD = 0x0;
                    //可用
                    const quint8 USABLE = 0x1;
                    //正在下载
                    const quint8 DOWNING = 0x2;
                    //下载出错
                    const quint8 DOWNERROR = 0x3;
                    //下载成功
                    const quint8 DOWNSUCCESS = 0x4;
                    //不可解析
                    const quint8 UNPARSE = 0x5;
                    //可解析
                    const quint8 PARSEABLE = 0x6;
                    //正在解析
                    const quint8 PARSING = 0x7;
                    //解析失败
                    const quint8 PARSEERROR = 0x8;
                    //解析成功
                    const quint8 PARSESUCCESS = 0x9;
                    //任务处理失败
                    const quint8 TASKERROR = 0xA;
                    //任务处理成功
                    const quint8 TASKSUCCESS = 0xB;

                }
                //下发文件处理表状态
                namespace SendFiles_State
                {
                    //废弃
                    const quint8 DISCARD = 0x0;
                    //可用
                    const quint8 USABLE = 0x1;
                    //正在下载
                    const quint8 DOWNING = 0x2;
                    //下载出错
                    const quint8 DOWNERROR = 0x3;
                    //下载成功
                    const quint8 DOWNSUCCESS = 0x4;
                    //不可解析
                    const quint8 UNPARSE = 0x5;
                    //可解析
                    const quint8 PARSEABLE = 0x6;
                    //正在解析
                    const quint8 PARSING = 0x7;
                    //解析失败
                    const quint8 PARSEERROR = 0x8;
                    //解析成功
                    const quint8 PARSESUCCESS = 0x9;
                 }
            }
            //控制传输任务状态
            namespace Sche
            {
                //任务表状态
                namespace Task_State
                {
                    //废弃
                    const quint8 DISCARD = 0x0;
                    //可用
                    const quint8 USABLE = 0x1;
                    //正在下载
                    const quint8 DOWNING = 0x2;
                    //下载出错
                    const quint8 DOWNERROR = 0x3;
                    //下载成功
                    const quint8 DOWNSUCCESS = 0x4;
                    //不可执行
                    const quint8 UNEXEC = 0x5;
                    //可执行
                    const quint8 EXECABLE = 0x6;
                    //正在执行
                    const quint8 EXECING = 0x7;
                    //执行失败
                    const quint8 EXECERROR = 0x8;
                    //执行成功
                    const quint8 EXECSUCCESS = 0x9;
                    //任务处理失败
                    const quint8 TASKERROR = 0xA;
                    //任务处理成功
                    const quint8 TASKSUCCESS = 0xB;
                }
                //下发文件处理表状态
                namespace SendFiles_State
                {
                    //废弃
                    const quint8 DISCARD = 0x0;
                    //可用
                    const quint8 USABLE = 0x1;
                    //正在下载
                    const quint8 DOWNING = 0x2;
                    //下载出错
                    const quint8 DOWNERROR = 0x3;
                    //下载成功
                    const quint8 DOWNSUCCESS = 0x4;
                    //不可执行
                    const quint8 UNEXEC = 0x5;
                    //可执行
                    const quint8 EXECABLE = 0x6;
                    //正在执行
                    const quint8 EXECING = 0x7;
                    //执行失败
                    const quint8 EXECERROR = 0x8;
                    //执行成功
                    const quint8 EXECSUCCESS = 0x9;
                 }
            }
        }
        //远程UI状态定义
        namespace Remoter
        {

        }
    }
    /////////////////////////////////////////////////////////////////处理任务状态end

    /////////////////////////////////////////////////////////////////报文定义begin
    namespace Datagram
    {
        //状态
        namespace State
        {
            //成功
            const quint8 _0 = 0x0;const QString _0_DESC_Success = trs("成功");
            //解析报文体失败
            const quint8 _1 = 0x1;const QString _1_DESC_ParseDatagramError = trs("解析报文体失败 ");
            //报文类型为空
            const quint8 _2 = 0x2;const QString _2_DESC_DatagramTypeIsNull = trs("报文类型为空");
            //报文类型不匹配
            const quint8 _3 = 0x3;const QString _3_DESC_DatagramUnmatched = trs("报文类型不匹配 ");
            //固定码为空
            const quint8 _4 = 0x4;const QString _4_DESC_UUIDIsNull = trs("固定码为空 ");
            //请求码为空
            const quint8 _5 = 0x5;const QString _5_DESC_RequestIDIsNull = trs("请求码为空 ");
            //任务编号为空
            const quint8 _6 = 0x6;const QString _6_DESC_TaskNumIsNull = trs("任务编号为空");
            //执行策略为空
            const quint8 _7 = 0x7;const QString _7_DESC_StrategyIsNull = trs("执行策略为空");
        }
        //长连接
        namespace Bridge_Conn
        {
            //长连接公用状态码
            namespace State
            {
                //解析报文出错
                const quint8 _8 = 0x8;
                //获取公钥码为空
                const quint8 _9 = 0x9;
                //公钥码长度不够32位
                const quint8 _10 = 0xA;
            }
            //节点向中心请求建立长连接
            const quint8 REQBRIDGECONN = 0x1;
            //中心响应长连接请求
            const quint8 RESPBRIDGECONN = 0x2;
            //节点向中心请求建立长连接状态码
            namespace Req_Info_State
            {
                //pubKey为空
                const quint8 _11 = 0xB;const QString _11_DESC_PubKeyIsEmpty = trs("公钥为空");
                //pubKey为空
                const quint8 _12 = 0xB;const QString _12_DESC_PriKeyIsEmpty = trs("私钥为空");
                //MAC为空
                const quint8 _13 = 0xC;const QString _13_DESC_MacAddrIsEmpty = trs("MAC地址为空");
            }
            //中心响应节点连接状态码
            namespace Resp_Info_State
            {
               //可信长连接池已满
               const quint8 _11 = 0xB;
            }
        }
        //心跳连接
        namespace Heartthrob_Conn
        {
            //心跳连接公用状态码
            namespace State
            {
                //解析报文出错
                const quint8 _8 = 0x8;
            }
            //节点向中心请求心跳连接
            const quint8 REQHEARTTHROBSCONN = 0x3;
            //中心响应节点心跳请求
            const quint8 RESPHEARTTHROBSCONN = 0x4;
            //节点向中心请求心跳连接状态码
            namespace Req_Info_State
            {

            }
            //中心响应节点连接状态码
            namespace Resp_Info_State
            {
               //可信心跳连接池已满
               const quint8 _8 = 0x8;
            }
        }
        //非结构化数据传输
        namespace Unstru_Data_Trans
        {
            //非结构化公用状态码
            namespace State
            {
            }
            //中心分发节点非结构文件组下载任务
            const quint8 REQUNSTRUCTFILESDOWNLOADINFO = 0x5;
            //节点响应中心收到非结构文件组下载请求
            const quint8 RESPUNSTRUCTFILESDOWNLOADINFO = 0x6;
            //节点下载完成反馈下载任务状况给中心
            const quint8 REQUNSTRUCTFILESDOWNLOADSTATUS = 0x7;
            //中心收到节点下载任务状况回执给节点
            const quint8 RESPUNSTRUCTFILESDOWNLOADSTATUS = 0x8;

            //操作类型码
            enum Unstru_Operate
            {
                Add,
                Delete,
                Modify
            };

            //下载策略码
            namespace Unstru_Down_Strategy
            {                
                //有文件出错，停止继续下载，立刻反馈出错信息，但是不反馈未下载文件
                const quint16 DS_1 = 0x1;
                //有文件出错，继续下载，并反馈出错文件
                const quint16 DS_2 = 0x2;
                //总反馈下载成功
                const quint16 DS_3 = 0x3;
                //保留
                const quint16 DS_4 = 0x4;
                //保留
                const quint16 DS_5 = 0x5;
                //保留
                const quint16 DS_6 = 0x6;
                //保留
                const quint16 DS_7 = 0x7;
                //保留
                const quint16 DS_8 = 0x8;
            }
            //中心分发节点非结构文件组下载任务状态码
            namespace Req_Info_State
            {
            }
            //节点响应中心收到非结构文件组下载请求状态码
            namespace Resp_Info_State
            {
                //8开始
                //解析文件下载地址失败
                const quint8 _8 = 0x8; const QString _8_DESC_ParseFileDownLoadAddrFail = trs("解析文件下载地址失败");
                //解析文件保存地址失败
                const quint8 _9 = 0x9; const QString _9_DESC_ParseFileSaveAddrFail = trs("解析文件保存地址失败");
                //创建非结构化任务入库失败
                const quint8 _A = 0xA; const QString _A_DESC_DBTransactionFail = trs("非结构化任务入库失败");
            }
            //节点下载完成反馈下载任务状况给中心状态码
            namespace Req_Info_Unstru_Down
            {
                //状态码为空
                const quint8 _8 = 0x8; const QString _8_DESC_StateIsNull = trs("状态码为空 ");
            }
            //中心收到节点下载任务状况回执给节点状态码
            namespace Resp_Info_Unstru_Down
            {
            }

        }
        //结构化数据传输
        namespace Stru_Data_Trans
        {
            //结构化公用状态码
            namespace State
            {

            }
            //中心分发节点结构数据文件组下载任务
            const quint8 REQSTRUCTFILESDOWNLOADINFO = 0x9;
            //节点响应中心收到结构文件组下载请求
            const quint8 RESPSTRUCTFILESDOWNLOADINFO = 0xA;
            //节点下载完成反馈下载任务状况给中心
            const quint8 REQSTRUCTFILESDOWNLOADSTATUS = 0xB;
            //中心收到节点下载任务状况回执给节点
            const quint8 RESPSTRUCTFILESDOWNLOADSTATUS = 0xC;
            //节点解析数据文件状况反馈给中心
            const quint8 REQSTRUCTTASKEXECSTATUS = 0xD;
            //中心收到节点解析数据文件状况回执给节点
            const quint8 RESPSTRUCTTASKEXECSTATUS = 0xE;

            //操作类型码
            enum Stru_Operate
            {
                Add,
                Delete,
                Modify
            };

            //执行策略包括数据文件下载策略和数据文件解析策略，策略码定义
            namespace Stru_Exec_Strategy
            {
                //有文件出错，停止继续下载，立刻反馈出错信息，但是不反馈未下载文件
                const quint16 ES_1 = 0x1;
                //有文件出错，继续下载，并反馈出错文件
                const quint16 ES_2 = 0x2;
                //总反馈下载成功
                const quint16 ES_3 = 0x3;
                //保留
                const quint16 ES_4 = 0x4;
                //保留
                const quint16 ES_5 = 0x5;
                //解析出错，回滚，反馈出错
                const quint16 ES_6 = 0x6;
                //解析出错，回滚，总反馈成功
                const quint16 ES_7 = 0x7;
                //保留
                const quint16 ES_8 = 0x8;
            }
            //中心分发节点结构数据文件组下载任务状态码
            namespace Req_Info_State
            {
            }
            //节点响应中心收到结构文件组下载请求状态码
            namespace Resp_Info_State
            {
            //8开始
                //执行时刻为空
                const quint8 _8 = 0x8; const QString _8_DESC_ExecTimeIsNull = trs("执行时刻为空");
                //执行时刻不符合日期格式yyyy-mm-dd hh:mm:ss
                const quint8 _9 = 0x9; const QString _9_DESC_ExecTimeFormatError = trs("执行时刻不符合日期格式yyyy-mm-dd hh:mm:ss");
                //解析文件下载地址失败
                const quint8 _A = 0xA; const QString _A_DESC_ParseFileDownLoadAddrFail = trs("解析文件下载地址失败");
                //解析文件保存地址失败
                const quint8 _B = 0xB; const QString _B_DESC_ParseFileSaveAddrFail = trs("解析文件保存地址失败");
                //创建结构化任务入库失败
                const quint8 _C = 0xC; const QString _C_DESC_DBTransactionFail = trs("创建结构化任务入库失败 ");

            }
            //节点下载完成反馈下载任务状况给中心状态码
            namespace Req_Info_Stru_Down
            {
            }
            //中心收到节点下载任务状况回执给节点状态码
            namespace Resp_Info_Stru_Down
            {
//                0x8	00001000	反序列化报文体失败，状态码为空
            }
            //节点解析数据文件状况反馈给中心状态码
            namespace Req_Info_Stru_Back
            {
            }
            //中心收到节点解析数据文件状况回执给节点状态码
            namespace Resp_Info_Stru_Back
            {
            }
        }
        //控制传输
        namespace Sche_Data_Trans
        {
            //控制传输公用状态码
            namespace State
            {
                //解析报文出错
                const quint8 _8 = 0x8;
                //任务编号为空
                const quint8 _9 = 0x9;
                //执行时刻为空
                const quint8 _10 = 0xA;
                //执行策略为空
                const quint8 _11 = 0xB;
                //执行入口文件名
                const quint8 _12 = 0xC;
            }
            //中心分发节点预执行任务文件组下载任务
            const quint8 REQSCHEDULETASKDOWNLOADINFO = 0xF;
            //节点响应中心收到预执行任务文件组下载请求
            const quint8 RESPSCHEDULETASKDOWNLOADINFO = 0x10;
            //节点下载完成反馈下载任务状况给中心
            const quint8 REQSCHEDULETASKDOWNLOADSTATUS = 0x11;
            //中心收到节点下载任务状况回执给节点
            const quint8 RESPSCHEDULETASKDOWNLOADSTATUS = 0x12;
            //节点执行任务状况反馈给中心
            const quint8 REQSCHEDULETASKEXECSTATUS = 0x13;
            //中心收到节点执行任务状况回执给节点
            const quint8 RESPSCHEDULETASKEXECSTATUS = 0x14;

            //操作类型码
            enum Sche_Operate
            {
                Add,
                Delete,
                Modify
            };

            //执行策略包括数据文件下载策略和数据文件解析策略，策略码定义
            namespace Sche_Exec_Strategy
            {                
                //有文件出错，停止继续下载，立刻反馈出错信息，但是不反馈未下载文件
                const quint16 ES_1 = 0x1;
                //有文件出错，继续下载，并反馈出错文件
                const quint16 ES_2 = 0x2;
                //总反馈下载成功
                const quint16 ES_3 = 0x3;
                //保留
                const quint16 ES_4 = 0x4;
                //保留
                const quint16 ES_5 = 0x5;
                //解析出错，回滚，反馈出错
                const quint16 ES_6 = 0x6;
                //解析出错，回滚，总反馈成功
                const quint16 ES_7 = 0x7;
                //保留
                const quint16 ES_8 = 0x8;
            }
            //中心分发节点预执行任务文件组下载任务状态码
            namespace Req_Info_State
            {

            }
            //节点响应中心收到预执行任务文件组下载请求状态码
            namespace Resp_Info_State
            {
            //8开始
                //执行时刻为空
                const quint8 _8 = 0x8; const QString _8_DESC_ExecTimeIsNull = trs("执行时刻为空");
                //执行时刻不符合日期格式yyyy-mm-dd hh:mm:ss
                const quint8 _9 = 0x9; const QString _9_DESC_ExecTimeFormatError = trs("执行时刻不符合日期格式yyyy-mm-dd hh:mm:ss");
                //入口文件保存路径为空
                const quint8 _A = 0xA; const QString _A_DESC_SaveAbstIsNull = trs("入口文件保存路径为空");                
                //解析文件下载地址失败
                const quint8 _B = 0xB; const QString _B_DESC_ParseFileDownLoadAddrFail = trs("解析文件下载地址失败");
                //解析文件保存地址失败
                const quint8 _C = 0xC; const QString _C_DESC_ParseFileSaveAddrFail = trs("解析文件保存地址失败");
                //创建结构化任务入库失败
                const quint8 _D = 0xD; const QString _D_DESC_DBTransactionFail = trs("创建结构化任务入库失败 ");
            }
            //节点下载完成反馈下载任务状况给中心状态码
            namespace Req_Info_Plan_Down
            {
            }
            //中心收到节点下载任务状况回执给节点状态码
            namespace Resp_Info_Plan_Down
            {
                //文件下载出错
                const quint8 _9 = 0x9;
            }
            //节点执行任务状况反馈给中心状态码
            namespace Req_Info_Plan_Back
            {
                //解析执行任务JSON串为空
                const quint8 _9 = 0x9; const QString _9_DESC_ParseJsonNull = trs("解析执行任务JSON串为空 ");
                //解析执行任务JSON串失败
                const quint8 _A = 0xA; const QString _A_DESC_ParseJsonError = trs("解析执行任务JSON串失败 ");
                //执行线程启动失败
                const quint8 _B = 0xB; const QString _B_DESC_ExecStartError = trs("执行线程启动失败");
                //解析执行任务反馈结果JSON串为空
                const quint8 _C = 0xC; const QString _C_DESC_ReturnJsonNull = trs("解析执行任务反馈结果JSON串为空 ");
                //解析执行任务反馈结果JSON串解析失败
                const quint8 _D = 0xD; const QString _D_DESC_ReturnJsonError = trs("解析执行任务反馈结果JSON串解析失败 ");
            }
            //中心收到节点执行任务状况回执给节点状态码
            namespace Resp_Info_Plan_Back
            {
            }
        }
        //监控部分
        namespace Monit_Ctrl
        {
            //监控公用状态码
            namespace State
            {                
                //解析报文出错
                const quint8 _8 = 0x8;
                //指标类型码为空
                const quint8 _9 = 0x9;
            }
            //中心发起获取节点指标
            const quint8 REQMONITORINGINDICATORINFO = 0x15;
            //节点响应中心收到获取指标请求
            const quint8 RESPMONITORINGINDICATORINFO = 0x16;
            //节点发送指标给中心
            const quint8 REQMONITORINGINDICATORSTATUS = 0x17;
            //中心响应收到指标
            const quint8 RESPMONITORINGINDICATORSTATUS = 0x18;

            //指标类型码
            namespace Index_Type
            {
                //用户及应用数据
                namespace UserApp
                {
                    //运维管理系统Operation and maintenance management system
                    const quint16 OPERA_MAINTEN = 0x101;
                    //电子政务系统Electronic government affairs system
                    const quint16 ELEC_AFFAIR = 0x102;
                }
                //操作系统数据
                namespace System
                {
                    //操作系统类型
                    const quint16 SYS_TYPE = 0x201;
                    //操作系统版本号
                    const quint16 SYS_VERSION = 0x202;
                }
            }
            //中心发起获取节点指标状态码
            namespace Req_Info_State
            {
            }
            //节点响应中心收到获取指标请求状态码
            namespace Resp_Info_State
            {
            }
            //节点发送指标给中心状态码
            namespace Req_Info_Back
            {
            }
            //中心响应收到指标状态码
            namespace Resp_Info_Back
            {
            }
        }
        //远程UI监控控制中心
        namespace UI_Ctrl
        {
            //远程UI监控控制中心公用状态码
            namespace State
            {
                //解析报文出错
                const quint8 _8 = 0x8;
                //操作类型码为空
                const quint8 _9 = 0x9;
            }
            //远程UI客户端请求中心建立长连接
            const quint8 REQREMOTEUIOPERACENTORCONN = 0x19;
            //中心响应远程UI建立长连接状态
            const quint8 RESPREMOTEUIOPERACENTORCONN = 0x1A;
            //远程UI请求中心操作数据
            const quint8 REQREMOTEUIOPERACENTORINFO = 0x1B;
            //中心返回远程UI请求数据
            const quint8 RESPREMOTEUIOPERACENTORINFO = 0x1C;

            //网络传输分隔符,做md5会使用该生成的字符串做分隔符
            const QString TransSeparator = trs("fc0f4b1e-f9c2-45d1-8f1d-b60056aba3a4");


            ////TODO    做远程UI时定义 ^_^
            //操作类型码定义,"""不能重复""",两个字节,字节1代表操作类型,字节2代表操作项,操作项最多为255
            namespace Opera_Type
            {
                //监控模块, 取值范围[0x101-0x1FF]
                namespace Monitor_Module
                {
                    //查询监控列表
                    const quint16 LIST_MONITOR_ITEM = 0x101;
                    //查看监控项详细数据
                    const quint16 MONITOR_ITEM_DETAIL = 0x102;
                }
                //数据控制模块, 取值范围[0x201-0x2FF]
                namespace Control_Module
                {
                    //非结构化功能
                    //查询任务列表
                    const quint16 Unstruct_listTask = 0x201;
                    //添加任务
                    const quint16 Unstruct_addTask = 0x202;
                    //begin xgd:
                    //添加任务节点服务器
                    const quint16 Unstruct_addTaskNode = 0x206;
                    //添加任务文件
                    const quint16 Unstruct_addTaskFile = 0x207;
                    //end xgd
                    //删除任务
                    const quint16 Unstruct_delTask = 0x203;
                    //查询可下发的节点服务器
                    const quint16 Unstruct_listNodeTask = 0x204;
                    //查看任务信息
                    const quint16 Unstruct_itemTask = 0x205;
                    //删除任务节点服务器
                    const quint16 Unstruct_delTaskNode = 0x210;
                    //删除任务文件
                    const quint16 Unstruct_delTaskFile = 0x211;
                    //修改任务信息
                    const quint16 Unstruct_updTask = 0x212;
                    //查询任务文件
                    const quint16 Unstruct_listFile = 0x213;
                    //修改任务节点服务器
                    const quint16 Unstruct_updateTaskNode = 0x214;
                    //修改任务关联表状态
                    const quint16 Unstruct_updateStatus = 0x215;
                    //查询任务关联表
                    const quint16 Unstruct_listStatus = 0x216;
                    //修改文件信息
                    const quint16 Unstruct_updateTaskFile = 0x217;
                    //字典管理
                    //添加字典
                    const quint16 Dict_add = 0x218;
                    //查询字典
                    const quint16 Dict_list = 0x219;
                    //删除字典
                    const quint16 Dict_del = 0x220;
                    //修改字典
                    const quint16 Dict_update = 0x221;

                    ////节点服务群组维护
                    //群组管理 添加群组
                    const quint16 Group_addClientGroup = 0x226;
                    //群组管理 修改群组
                    const quint16 Group_updClientGroup = 0x227;
                    //群组管理 查询群组
                    const quint16 Group_listClientGroup = 0x228;
                    //群组管理 添加节点服务器
                    const quint16 Group_addGroupNode = 0x229;
                    //群组管理 删除群组
                    const quint16 Group_delGroupNode = 0x230;
                    //群组管理 获取节点服务器
                    const quint16 Group_listGroupNode = 0x231;
                    //群组管理 删除节点服务器
                    const quint16 Group_delClientGroup = 0x232;
                    //群组管理 改变群组中节点的位置
                    const quint16 Group_moveSequence = 0x233;
                    //群组管理 修改节点服务器状态
                    const quint16 Group_updateGroupNode = 0x234;
                    //群组管理 模糊查询节点服务器扩展信息
                    const quint16 Group_listExtendInfo = 0x235;
                    ////结构化查询列表
                    //查询任务列表
                    const quint16 Struct_listTask = 0x241;
                    //添加任务
                    const quint16 Struct_addTask = 0x242;
                    //begin xgd:
                    //添加任务节点服务器
                    const quint16 Struct_addTaskNode = 0x246;
                    //添加任务文件
                    const quint16 Struct_addTaskFile = 0x247;
                    //end xgd
                    //删除任务
                    const quint16 Struct_delTask = 0x243;
                    //查询可下发的节点服务器
                    const quint16 Struct_listNodeTask = 0x244;
                    //查看任务信息
                    const quint16 Struct_itemTask = 0x245;
                    //删除任务节点服务器
                    const quint16 Struct_delTaskNode = 0x250;
                    //删除任务文件
                    const quint16 Struct_delTaskFile = 0x251;
                    //修改任务信息
                    const quint16 Struct_updTask = 0x252;
                    //查询任务文件
                    const quint16 Struct_listFile = 0x253;
                    //修改任务节点服务器
                    const quint16 Struct_updateTaskAddr = 0x254;
                   // 修改任务关联状态
                    const quint16 Struct_updateStatus = 0x255;
                    //查询任务关联表
                    const quint16 Struct_listStatus = 0x256;
                    //修改文件信息
                    const quint16 Struct_updateTaskFile = 0x257;

                    ////控制传输
                    //查询控制传输任务指定的任务一条信息
                    const quint16 Schedule_itemTask = 0x316;
                    //查询控制传输任务所有信息列表
                    const quint16 Schedule_listTask = 0x318;
                    //删除控制传输任务信息
                    const quint16 Schedule_delTask = 0x319;
                    //更改控制传输任务信息
                    const quint16 Schedule_updateTask = 0x320;
                    //增加控制传输任务信息
                    const quint16 Schedule_addTask = 0x321;
                    //查询控制传输下发地址信息
                    const quint16 Schedule_listAddr = 0x322;
                    //删除控制传输下发地址信息
                    const quint16 Schedule_delAddr = 0x323;
                    //更改控制传输下发地址信息
                    const quint16 Schedule_updateAddr = 0x324;
                    //增加控制传输下发地址信息
                    const quint16 Schedule_addAddr = 0x325;
                    //查询控制传输下发文件信息
                    const quint16 Schedule_listFiles = 0x326;
                    //删除控制传输下发文件信息
                    const quint16 Schedule_delFiles = 0x327;
                    //更改控制传输下发文件信息
                    const quint16 Schedule_updateFiles = 0x328;
                    //增加控制传输下发文件信息
                    const quint16 Schedule_addFiles = 0x329;
                    //修改控制传输下发关联状态
                    const quint16 Schedule_updateStatus = 0x330;
                    //查询任务关联表
                    const quint16 Schedule_listStatus = 0x331;
                    //修改文件信息
                    const quint16 Schedule_updateTaskFile = 0x332;
                }
            }

            //远程UI客户端请求中心建立长连接状态码
            namespace Req_Info_State
            {
            }
            //中心响应远程UI建立长连接状态状态码
            namespace Resp_Info_State
            {
            }
            //远程UI请求中心操作数据状态码
            namespace Req_Info_Operate
            {
            }
            //中心返回远程UI请求数据状态码
            namespace Resp_Info_Operate
            {
            }
        }

        namespace Web_Serverlet
        {
            namespace DDEditor
            {
                namespace Opera_Type
                {
                    //下发任务
                    const quint16 Task_send = 0x400;
                    //删除任务
                    const quint16 Task_del = 0x401;
                }
                namespace Send
                {
                    namespace state
                    {
                        const quint8 _1 = 0x1;const QString _1_DESC_CreateHardLinkFail = trs("创建硬链接失败 ");

                        const quint8 _2 = 0x2;const QString _2_DESC_DestoryDirFail = trs("销毁本次任务目录失败  ");

                        const quint8 _3 = 0x3;const QString _3_DESC_CreateRespondJsonFail = trs("创建任务反馈JSON失败");

                    }
                }
            }

        }
    }
    /////////////////////////////////////////////////////////////////报文定义end
    ////////////////////////////// 定义关于树的常量 分批取///////////////////////////////////
    enum TreePage{
       PAGE_NUM = 1000
    };

}
#endif // CONSTANT

