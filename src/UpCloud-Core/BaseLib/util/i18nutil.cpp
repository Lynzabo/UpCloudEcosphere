#include "i18nutil.h"
#include <QTranslator>
#include <QLibraryInfo>
#include <QLocale>
#include <QCoreApplication>
#include "pathutil.h"
#include <QDebug>
void I18NUtil::installTranslator(const QString &m_dir)
{
//    QTranslator m_apTranslator,m_qtTranslator;
//    const QString execName = PathUtil::getInstance().executeName();
//    m_apTranslator.load(":/" + m_dir + "/" + execName
//            + "_" + QLocale::system().name() + ".qm");
//    m_qtTranslator.load("qt_" + QLocale::system().name(),
//            QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    //Qt classwizard demo
    /*QString translatorFileName = QLatin1String("qt_");
         translatorFileName += QLocale::system().name();
         QTranslator *translator = new QTranslator(&app);
         if (translator->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
             app.installTranslator(translator);
*//*QTranslator *translator = new QTranslator(qApp);
    translator->load(":/image/qt_zh_CN.qm");
    qApp->installTranslator(translator);*/
    /*QTranslator m_apTranslator,m_qtTranslator;
    const QString execName = PathUtil::getInstance().executeName();
    m_apTranslator.load(":/" + m_dir + "/" + execName
                + "_" + QLocale::system().name() + ".qm");
    m_qtTranslator.load(":/" + m_dir + "/qt_"
                + "_" + QLocale::system().name() + ".qm");
    QCoreApplication::installTranslator(&m_qtTranslator);
    QCoreApplication::installTranslator(&m_apTranslator);*/
    QTranslator m_apTranslator,m_qtTranslator;
    m_apTranslator.load(":/core/i18n/i18n/StartRemoteUI_zh_CN");
    m_qtTranslator.load(":/core/i18n/i18n/qt_zh_CN");
    QCoreApplication::installTranslator(&m_qtTranslator);
    QCoreApplication::installTranslator(&m_apTranslator);
}

SINGLETON_ALL_IN_ONE(I18NUtil)


