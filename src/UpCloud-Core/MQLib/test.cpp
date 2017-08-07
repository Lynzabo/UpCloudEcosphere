/*#include <QtCore>
#include "mq.h"
int main()
{
    MQPool::getInstance();
    class GetTokenRunnable : public QRunnable
    {
    public:
        void run()
        {
            //生成一个生产者
            Producer *producer = MQPool::getInstance().genProducer();
            producer->setMsg();
            //阻塞工作,产生一个结构集合,放消费者不对
            Consumer *consumer = MQPool::getInstance().doWork(producer,MessageTopic::HighPriority);
            MQPool::getInstance().close(producer);
        }
    };
    //
    QThreadPool::globalInstance()->start(new GetTokenRunnable);


    MQPool::release();
    return 0;
}*/
//#include <QtCore>
//#include "mq.h"
/*
class ListUnstructTask:FDuplex{
public:
    ListUnstructTask(MessageTopic::Priority priority = MessageTopic::NormalPriority);
protected:
    virtual void onPreExecute()
    {
        ui->loading.setText("开始工作");
    }
    virtual void doInBackground()
    {
        Message *msg = new Message;
        emit
            evt_send(msg);
    }
    virtual void callback(Message *msg)
    {
        bool status = QDataStream::fromData(msg);
    }
    virtual void onPostExecute()
    {
        ui->loading.setText("工作完成");
    }
};
int main()
{
    MQPool::getInstance();
    MQPool::getInstance().start(new ListUnstructTask(MessageTopic::HighPriority));
    MQPool::release();
    return 0;
}*/
/*
class Worker:QWidget{
public slots:
    void onbtn_click()
    {
        //MQPool::getInstance();
        //另外可以加成AsyncTask模式,在该类中可以操作UI,当前模式要操作UI，必须关联信号到外面UI
        class GetTokenRunnable : public QRunnable
        {
        public:
            void run()
            {
                Producer producer = MQPool::getInstance().genProducer(MessageTopic::HighPriority);//生成消费者
                produer.setMsg(msg);//存放报文进入
                Consumer consumer = MQPool::getInstance().work(producer);//阻塞去工作
                consumer.getCallMsg();//获取结果集
            }
        };
        //
        QThreadPool::globalInstance()->start(new GetTokenRunnable);
    }
};
int main()
{
    MQPool::getInstance();
    Worker worker;
    worker.show();
    MQPool::release();
    return 0;
}*/
