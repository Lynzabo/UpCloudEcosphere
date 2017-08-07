#ifndef UIHELPER_H
#define UIHELPER_H
#include <QtCore>
#include <QObject>
#include <QtWidgets>
#include <QApplication>
#include "rmessagebox.h"
class UIHelper : public QObject
{
    Q_OBJECT
private:
    explicit UIHelper(QObject *parent = 0);
public:
    /**
     * @brief AutoRunWithSystem 设置为开机启动
     * @param IsAutoRun
     * @param AppName
     * @param AppPath
     */
    static void AutoRunWithSystem(bool IsAutoRun, QString AppName, QString AppPath)
    {
        QSettings *reg = new QSettings(
            "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
            QSettings::NativeFormat);

        if (IsAutoRun) {
            reg->setValue(AppName, AppPath);
        } else {
            reg->setValue(AppName, "");
        }
    }
    /**
     * @brief SetUTF8Code   设置编码为UTF8
     */
    static void SetUTF8Code()
    {
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QTextCodec::setCodecForLocale(codec);
        QTextCodec::setCodecForCStrings(codec);
        QTextCodec::setCodecForTr(codec);
#endif
    }
    /**
     * @brief SetStyle  设置皮肤样式
     * @param styleName
     */
    static void SetStyle(QApplication &app,const QString &styleName)
    {
        QFile file(QString(":/image/%1.css").arg(styleName));
        file.open(QFile::ReadOnly);
        QString qss = QLatin1String(file.readAll());
        app.setStyleSheet(qss);
        qApp->setPalette(QPalette(QColor("#F0F0F0")));
    }

    /**
     * @brief SetChinese    加载中文字符
     */
    static void SetChinese()
    {
        QTranslator *translator = new QTranslator(qApp);
        translator->load(":/image/qt_zh_CN.qm");
        qApp->installTranslator(translator);
    }

    /**
     * @brief IsIP  判断是否是IP地址
     * @param IP
     * @return
     */
    static bool IsIP(QString IP)
    {
        QRegExp RegExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
        return RegExp.exactMatch(IP);
    }
    /**
     * @brief Sleep 延时
     * @param sec
     */
    static void Sleep(int sec)
    {
        QTime dieTime = QTime::currentTime().addMSecs(sec);
        while ( QTime::currentTime() < dieTime ) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
    }

    /**
     * @brief FormInCenter  窗体居中显示
     * @param frm
     */
    static void FormInCenter(QWidget *frm)
    {
        int frmX = frm->width();
        int frmY = frm->height();
        QDesktopWidget w;
        int deskWidth = w.width();
        int deskHeight = w.height();
        QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeight / 2 - frmY / 2);
        frm->move(movePoint);
    }
    /**
     * @brief ShowMessageBoxInfo    显示信息框,仅确定按钮
     * @param info
     * UIHelper::ShowMessageBoxInfo(QString("确定操作确定操作吗？"));
     */
    static void ShowMessageBoxInfo(QString info)
    {
        RMessageBox *msg = new RMessageBox;
        msg->setMessage(info, RMessageBox::INFO);
        msg->exec();
    }

    /**
     * @brief ShowMessageBoxError   显示错误框,仅确定按钮
     * @param info
     * UIHelper::ShowMessageBoxError(QString("确定操作确定操作吗？"));
     */
    static void ShowMessageBoxError(QString info)
    {
        RMessageBox *msg = new RMessageBox;
        msg->setMessage(info, RMessageBox::ERR);
        msg->exec();
    }

    /**
     * @brief ShowMessageBoxQuesion 显示询问框,确定和取消按钮
     * @param info
     * @return
     * if(UIHelper::ShowMessageBoxQuesion(QString("确定操作确定操作吗？")) == QDialog::Accepted)
        {
            UIHelper::ShowMessageBoxInfo(QString("操作成功"));
        }
        else
        {
            UIHelper::ShowMessageBoxError(QString("操作失败"));
        }
     */
    static int ShowMessageBoxQuesion(QString info)
    {
        RMessageBox *msg = new RMessageBox;
        msg->setMessage(info, RMessageBox::QUESTION);
        return msg->exec();
    }

    /**
     * @brief ShowMessageBoxWarn    显示警告框,确定和取消,离开按钮
     * @param info
     * @return
     * int resultCode = UIHelper::ShowMessageBoxWarn(QString("确认离开吗？"));
    if( resultCode== QDialog::Accepted)
    {
        UIHelper::ShowMessageBoxInfo(QString("操作成功"));
    }
    else if( resultCode== QDialog::Rejected)
    {
        UIHelper::ShowMessageBoxError(QString("操作失败"));
    }
    else
    {
        UIHelper::ShowMessageBoxInfo(QString("离开"));
    }
     */
    static int ShowMessageBoxWarn(QString info)
    {
        RMessageBox *msg = new RMessageBox;
        msg->setMessage(info, RMessageBox::WARN);
        return msg->exec();
    }

    /**
     * @brief OpenInSelf
     * @param curWindow
     * @param openWidget
     */
    /**
     * @brief OpenInSelf    跳转到当前窗体
     * @param curWindow
     * @param openWidget
     * @param stackName 上级stackWidget名称     *该字段一般不要重写,直接使用默认的
     * 注意:所有Widget不能重名
     */
    static void OpenInSelf(QWidget *curWindow,QWidget *openWidget,const QString stackName = QString("sw_content"));
    /**
     * @brief OpenInTop 在当前窗体上打开窗体
     * @param curWindow
     * @param openWidget
     * @param stackName 上级stackWidget名称     *该字段一般不要重写,直接使用默认的
     * 注意:所有Widget不能重名
     */
    static void OpenInTop(QWidget *curWindow,QWidget *openWidget,const QString stackName = QString("sw_content"));
    /**
     * @brief showLoading   显示Loading
     * @param curWindow
     */
    static void showLoading(QWidget *curWindow,const QString &msg = tr("正在加载..."));
    /**
     * @brief hideLoading   隐藏Loading
     * @param curWindow
     */
    static void hideLoading(QWidget *curWindow);
signals:

public slots:
};

#endif // UIHELPER_H
