#ifndef CREATETASKINFO_H
#define CREATETASKINFO_H
#include <QtCore>

class CreateTaskInfo
{
public:
    CreateTaskInfo();


    QString getTaskName() const;
    void setTaskName(const QString &value);

    QString getSendTime() const;
    void setSendTime(const QString &value);

    QString getExecTime() const;
    void setExecTime(const QString &value);

    QString getParseTime() const;
    void setParseTime(const QString &value);

    quint8 getTaskState() const;
    void setTaskState(const quint8 &value);

    quint16 getStrategy() const;
    void setStrategy(const quint16 &value);

    QString getFileName() const;
    void setFileName(const QString &value);

    QString getClientUuid() const;
    void setClientUuid(const QString &value);

    QString getGroupDescription() const;
    void setGroupDescription(const QString &value);

    QString getClientDescription() const;
    void setClientDescription(const QString &value);

    quint8 getFileState() const;
    void setFileState(const quint8 &value);
    //TODO 可以先在实体中，以后分离开，也简单，因为引入太多文件不方便，也没有其他业务，所以就放在这了
    static void mapAddTaskInfoToJson(QString &msg, const CreateTaskInfo &info);
    static void mapAddTaskInfoToJson(QString &msg, const QList<CreateTaskInfo> &infoList);
    static bool mapAddTaskInfoFromJson(CreateTaskInfo &info,const QString &msg);
    static bool mapAddTaskInfoFromJson(QList<CreateTaskInfo> &infoList, const QString &msg);
private:
    //任务名称
    QString taskName;
    //任务下发时间
    QString sendTime;
    //任务执行时间
    QString execTime;
    //任务解析时间
    QString parseTime;
    //任务状态
    quint8 taskState;
    //任务策略
    quint16 strategy;
    //文件名
    QString fileName;
    //节点服务器固定码
    QString clientUuid;
    //节点服务器所属群组集合
    QString groupDescription;
    //节点服务器名称
    QString clientDescription;
    //文件状态
    quint8 fileState;

};

#endif // CREATETASKINFO_H
