﻿#include "widget.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "client.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    client cli = client();
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "client_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    Widget w;
    w.show();
    return a.exec();
}