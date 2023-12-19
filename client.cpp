#include "client.h"

client::client()
{
    char *data=(char*)"hello qt!";
    socket = new QTcpSocket();
    socket->connectToHost(QHostAddress("192.168.31.129"), 6000);
    socket->write(data);
}

