#include "client.h"
#include <QFile>
#include <QDataStream>
#include <QDialog>
#include <QMessageBox>
client::client(QObject *parent)
{

    socket = new QTcpSocket(parent);
    socket->connectToHost(QHostAddress("172.25.236.123"), 6000);
    connect(socket, SIGNAL(readyRead()), this ,SLOT(readData()));
}
void client::send(QString msg)
{
    //先发送文件头信息 文件名##文件大小
    QString head = QString("%1##%2##").arg("msg").arg(username);
    qDebug() << "filename: "<<head;
    //发送头部信息
    qint64 len = socket->write(head.toUtf8());
    socket->write(msg.toUtf8().data());
}
void client::readData()
{
    QString str = QString::fromUtf8(socket->readAll());
    if(str == QString::fromLocal8Bit("F#"))
    {
        QMessageBox msgBox;
        msgBox.setText("recv a file or not");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);

        int ret = msgBox.exec();

        if (ret == QMessageBox::Yes) {
            recv_buff = "you have recv a file";
            qDebug() << "Received data: " << recv_buff;
            recv_text();
        } else {
            recv_buff = "you reject recv a file";
            qDebug() << "Received data: " << recv_buff;
            recv_text();
        }

    }
    else{
        QStringList list = str.split("##");
        recv_buff = list[2];
        recvname = list[1];
        int flag = 1;
        for(QString a : online_people)
        {
           flag =  QString::compare(recvname,a);
           if(flag == 0)
           {
               break;
           }

        }
        if(flag == 1)
        {
            online_people.push_back(recvname);
            updateitem();
        }

        qDebug() << "Received data: " << recv_buff;
        recv_text();
    }
}
QString client::getBuffer()
{
   qDebug() << "recv_buff"<<recv_buff;
    return recv_buff;

}

void client::senFile(QString filename)
{


    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file for reading.";
        return;
    }

    if (socket->waitForConnected()) {
        //先发送文件头信息 文件名##文件大小
        QString head = QString("%1##%2##").arg(file.fileName()).arg(file.size());
        qDebug() << "filename: "<<head;
        //发送头部信息
        qint64 len = socket->write(head.toUtf8());

//        QDataStream out(socket);
////        out << qint64(0) << file.fileName(); // Send file name
//        out.device()->seek(0);
//        out << qint64(file.size()); // Send file size
        qint64 fileSize = file.size(); // 文件的长度
        int readSize = 1024 ;  // 每一次读取的数据长度，可以自由设置
        while(!file.atEnd())
        {
            QByteArray data = file.read(readSize );
            socket->write(data);

        }
        file.close();
    } else {
        qDebug() << "Failed to connect to the server.";
    }
}
