/*#include <QtCore>
#include "duplex.h"
int main()
{
    UpCloudDuplexFactory::getInstance();
    class GetTokenRunnable : public QRunnable
    {
    public:
        void run()
        {
            //1.生成一个消息发送端
            DPSender *sender = UpCloudDuplexFactory::getInstance().createDPSender();
            //2.准备请求数据
            if(!sender)
                return;
            sender->setExecType(Control_Module::Unstruct_listTask);
            sender->setParams("");
//            sender->setMsg();
            //3.配置额外参数
            //设置该请求5s过期,当过期时,doSendBySync返回0
//            sender->setExpiredTime(5);
            //4.获得结果集
            DPResult *resultSet = sender->doSendBySync(DeplexDefs::Priority::HighPriority);
            if(!resultSet)
                return;
            //5.使用结构集处理响应
            resultSet->getMsg();
            //6.销毁消息发送端,注意,该动作不能省略,并且释放完了后不需要delete sender指针
            sender->destory();
        }
    };
    //
    QThreadPool::globalInstance()->start(new GetTokenRunnable);


    UpCloudDuplexFactory::release();
    return 0;
}
*/
