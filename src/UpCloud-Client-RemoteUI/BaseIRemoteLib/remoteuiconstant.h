#ifndef REMOTEUICONSTANT
#define REMOTEUICONSTANT
#include "base.h"
//远程UI客户端系统常量定义
namespace RemoteUIEnvironment
{
    //工作线程与UI通信参数定义
    namespace CallbackStatus
    {
        namespace Unstruct
        {
            //成功
            const qint32 _0 = 10000000;const QString _0_Desc_SUCCESS = QObject::tr("操作成功");
            //访问地址无效
            const qint32 _1 = 10000001;const QString _1_Desc_AddrIsInvalid = QObject::tr("访问地址无效");
            //未授权访问地址
            const qint32 _2 = 10000002;const QString _2_Desc_Unauthorized = QObject::tr("没有访问权限,请联系系统管理员");
            //操作数据库失败
            const qint32 _3 = 10000003;const QString _3_Desc_DatabaseError = QObject::tr("操作数据库失败!");
            //解析参数失败
            const qint32 _4 = 10000004;const QString _4_Desc_ParamParseError = QObject::tr("解析参数失败");
            //网络连接断开
            const qint32 _5 = 10000005;const QString _5_Desc_SeiviceIsNull = QObject::tr("网络连接断开");
            //解析数据失败
            const qint32 _6 = 10000006;const QString _6_Desc_ParseDataError = QObject::tr("解析数据失败");
            //传递参数为空
            const qint32 _7 = 10000007;const QString _7_Desc_ParamsHasNullValue = QObject::tr("传递参数为空!");
            //添加记录已存在
            const  qint32 _8 = 10000008;const QString _8_Desc_RecordIsExist = QObject::tr("此记录已存在");
        }
        namespace Struct
        {
            const qint32 _0 = 10000000;const QString _0_Desc_SUCCESS = QObject::tr("操作成功");
            //访问地址无效
            const qint32 _1 = 10000001;const QString _1_Desc_AddrIsInvalid = QObject::tr("访问地址无效");
            //未授权访问地址
            const qint32 _2 = 10000002;const QString _2_Desc_Unauthorized = QObject::tr("没有访问权限,请联系系统管理员");
            //操作数据库失败
            const qint32 _3 = 10000003;const QString _3_Desc_DatabaseError = QObject::tr("操作数据库失败!");
            //解析参数失败
            const qint32 _4 = 10000004;const QString _4_Desc_ParamParseError = QObject::tr("解析参数失败");
            //网络连接断开
            const qint32 _5 = 10000005;const QString _5_Desc_SeiviceIsNull = QObject::tr("网络连接断开");
            //解析数据失败
            const qint32 _6 = 10000006;const QString _6_Desc_ParseDataError = QObject::tr("解析数据失败");
            //传递参数为空
            const qint32 _7 = 10000007;const QString _7_Desc_ParamsHasNullValue = QObject::tr("传递参数为空!");
            //添加记录已存在
            const  qint32 _8 = 10000008;const QString _8_Desc_RecordIsExist = QObject::tr("此记录已存在");
        }
        namespace Schedule
        {
            const qint32 _0 = 10000000;const QString _0_Desc_SUCCESS = QObject::tr("操作成功");
            //访问地址无效
            const qint32 _1 = 10000001;const QString _1_Desc_AddrIsInvalid = QObject::tr("访问地址无效");
            //未授权访问地址
            const qint32 _2 = 10000002;const QString _2_Desc_Unauthorized = QObject::tr("没有访问权限,请联系系统管理员");
            //操作数据库失败
            const qint32 _3 = 10000003;const QString _3_Desc_DatabaseError = QObject::tr("操作数据库失败!");
            //解析参数失败
            const qint32 _4 = 10000004;const QString _4_Desc_ParamParseError = QObject::tr("解析参数失败");
            //网络连接断开
            const qint32 _5 = 10000005;const QString _5_Desc_SeiviceIsNull = QObject::tr("网络连接断开");
            //解析数据失败
            const qint32 _6 = 10000006;const QString _6_Desc_ParseDataError = QObject::tr("解析数据失败");
            //传递参数为空
            const qint32 _7 = 10000007;const QString _7_Desc_ParamsHasNullValue = QObject::tr("传递参数为空!");
            //添加记录已存在
            const  qint32 _8 = 10000008;const QString _8_Desc_RecordIsExist = QObject::tr("此记录已存在");
        }
        namespace Basal {
            //成功
            const qint32 _0 = 10000000;const QString _0_Desc_SUCCESS = QObject::tr("操作成功");
            //访问地址无效
            const qint32 _1 = 10000001;const QString _1_Desc_AddrIsInvalid = QObject::tr("访问地址无效");
            //未授权访问地址
            const qint32 _2 = 10000002;const QString _2_Desc_Unauthorized = QObject::tr("没有访问权限,请联系系统管理员");
             //操作数据库失败
            const qint32 _3 = 10000003;const QString _3_Desc_DatabaseError = QObject::tr("操作数据库失败!");
            //解析参数失败
            const qint32 _4 = 10000004;const QString _4_Desc_ParamParseError = QObject::tr("解析参数失败");
            //网络连接断开
            const qint32 _5 = 10000005;const QString _5_Desc_SeiviceIsNull = QObject::tr("网络连接断开");
            //解析数据失败
            const qint32 _6 = 10000006;const QString _6_Desc_ParseDataError = QObject::tr("解析数据失败");
            //传递参数为空
            const qint32 _7 = 10000007;const QString _7_Desc_ParamsHasNullValue = QObject::tr("传递参数为空!");
            //记录已经存在
            const quint8 _8 = 10000008;const QString _8_DESC_RecordIsExsit = QObject::tr("记录已经存在");
        }
    }
}
#endif // REMOTEUICONSTANT

