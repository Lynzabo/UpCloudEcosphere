#ifndef TRANSMSG
#define TRANSMSG
//报文装帧格式
#include "datagraminfo.h"

//拼装报文辅助类
//#include "util/datagramutil.h"

//终端固定码UUID操作工具类
//#include "util/terminaluuidutil.h"
//所有报文传输的头文件

//长连接报文
#include "reqbridgeconn.h"
#include "respbridgeconn.h"
//心跳连接报文
#include "reqheartthrobsconn.h"
#include "respheartthrobsconn.h"
//非结构化传输报文
#include "requnstructfilesdownloadinfo.h"
#include "respunstructfilesdownloadinfo.h"
#include "requnstructfilesdownloadstatus.h"
#include "respunstructfilesdownloadstatus.h"
//结构化传输报文
#include "reqstructfilesdownloadinfo.h"
#include "respstructfilesdownloadinfo.h"
#include "reqstructfilesdownloadstatus.h"
#include "respstructfilesdownloadstatus.h"
#include "reqstructtaskexecstatus.h"
#include "respstructtaskexecstatus.h"
//控制传输
#include "reqscheduletaskdownloadinfo.h"
#include "respscheduletaskdownloadinfo.h"
#include "reqscheduletaskdownloadstatus.h"
#include "respscheduletaskdownloadstatus.h"
#include "reqscheduletaskexecstatus.h"
#include "respscheduletaskexecstatus.h"
//监控指标
#include "reqmonitoringindicatorinfo.h"
#include "respmonitoringindicatorinfo.h"
#include "reqmonitoringindicatorstatus.h"
#include "respmonitoringindicatorstatus.h"
//远程UI
#include "reqremoteuioperacentorconn.h"
#include "respremoteuioperacentorconn.h"
#include "reqremoteuioperacentorinfo.h"
#include "respremoteuioperacentorinfo.h"

#endif // TRANSMSG

