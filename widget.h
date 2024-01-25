#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "client.h"
#include <vector>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    QString selectedFilePath;
    QTcpSocket *tcpSocket;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QString buffer;
    client *cli;

    QString username;
    QString ip;
    Ui::Widget *ui;
    void conectserver();

private slots:
    void textTobuffer();
    void recvFrombuffer();
    void FileButton();
    void sendFileButton();
    void updateviewlists();
};
#endif // WIDGET_H
