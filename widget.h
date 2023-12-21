#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "client.h"
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
    Ui::Widget *ui;
private slots:
    void textTobuffer();
    void recvFrombuffer();
    void FileButton();
    void sendFileButton();
};
#endif // WIDGET_H
