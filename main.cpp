#include "widget.h"
#include "login.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <windows.h>
void hello()
{

}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "client_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    login l;
    l.show();

    Widget w;
    QObject::connect(&l, &login::loginSuccessful, [&]() {
        w.username = l.getusername();
        w.ip = l.getip();
        l.close();
        w.show();
        w.conectserver();
        w.cli->username = w.username;
    });
    return a.exec();
}

