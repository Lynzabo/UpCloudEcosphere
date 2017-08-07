#ifndef DOWNVIEW_H
#define DOWNVIEW_H
#include <QLabel>
#include <QtCore>
#include <QPushButton>
#include <QProgressBar>
#include <QWidget>
#include <QTime>
class DownView : public QProgressBar
{
    Q_OBJECT
public:
    DownView(QWidget* parent = 0);
    ~DownView();
    //终止任务
    void setEnd();
    //开始任务
    void setStart();
    //设置进度 时间 速度
    void setProcess(float per,const QString &str,const QString &time);
    //更新进度信息
    void updateInfo(quint64 haveDown, quint64 total);
    //设置错误信息
    void setError();
    //设置文件名
    void setFileName(const QString &name);
    //初始化进度条
    void initView();
    //下载完成
    void endDown();
    //暂停
    void pauseDown();
    //获取文件名
    QString fileName() const;

    quint32 dec() const;
    void setDec(const quint32 &dec);

    quint64 downBytes() const;
    void setDownBytes(const quint64 &downBytes);

    QTime curTime() const;
    void setCurTime(const QTime &curTime);

private slots:
    void on_end(bool flg);
    void on_start(bool flg);
signals:
    void evt_end(DownView* item);
private:
    //文件大小转换单位
    QString fileSizeUnit(quint64 &size);
    //下载速度大小转换单位
    QString speedUnit(double &size);
private:
    //开始按键
    QPushButton* m_btn_opt;
    //结束按键
    QPushButton* m_btn_end;
    //文件图标
    QLabel* m_lab_icon;
    //文件名字
    QLabel* m_lab_name;
    //速度大小和文件大小
    QLabel* m_lab_size;
    //剩余时间
    QLabel* m_lab_time;
    //存在本地的文件名
    QString m_fileName;
    //本地的路径名
    QString m_filePath;
    //当前时间
    QTime m_curTime;
    //下载的字节数
    quint64 m_downBytes;
    //用时
    quint32 m_dec;

    float m_curPer;
    bool m_flg;
};

#endif // DOWNVIEW_H
