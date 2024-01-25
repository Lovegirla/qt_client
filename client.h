#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork>
#include <QObject>
class client:public QObject
{
    Q_OBJECT
    QTcpSocket* socket;
    QString recv_buff;
private slots:
    void readData();

signals:
    void recv_text();
    void updateitem();
public:
    QString recvname;
    client(QObject *parent = nullptr);
    QString username;
    void send(QString msg);
    ~client(){
        socket->close();
    }
    QString getBuffer();
    void senFile(QString filename);
    QStringList  online_people;

};

#endif // CLIENT_H
