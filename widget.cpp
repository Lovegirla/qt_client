#include "widget.h"
#include "ui_widget.h"
#include "QDebug"
#include <QDateTime>
#include <QFileDialog>
#include <QTcpSocket>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    cli = new client(this);
    ui->setupUi(this);
    connect(ui->sendpushButton,SIGNAL(clicked()),this,SLOT(textTobuffer()));//响应发送信号事件
    connect(cli,SIGNAL(recv_text()),this,SLOT(recvFrombuffer()));//响应接收事件
    connect(ui->selectpushButton,SIGNAL(clicked()),this,SLOT(FileButton()));
    connect(ui->sendfilepushButton,SIGNAL(clicked()),this,SLOT(sendFileButton()));
    connect(cli,SIGNAL(updateitem()),this,SLOT(updateviewlists()));

}

Widget::~Widget()
{
    delete ui;
}
void Widget::textTobuffer()
{

  buffer = ui->sendtextEdit->toPlainText();
  cli->send(buffer);
  qDebug()<<"buffer find"<<endl;
  //buffer加上时间
   {

      QDateTime dateTime= QDateTime::currentDateTime();
      QString str = dateTime.toString("yyyy-MM-dd hh:mm:ss");
      buffer = str +username+"\n" + buffer;
   }
  ui->messagetextEdit->append(buffer);
  ui->sendtextEdit->clear();
}
void Widget::recvFrombuffer()
{
    buffer = cli->getBuffer();

    QDateTime dateTime= QDateTime::currentDateTime();
    QString str = dateTime.toString("yyyy-MM-dd hh:mm:ss");
    buffer = str + cli->recvname + "\n" + buffer;

    ui->messagetextEdit->append(buffer);
}
//点击选择文件时，找到文件目录
void Widget::FileButton()
{
    selectedFilePath = QFileDialog::getOpenFileName(this, "Select File to Send");
    qDebug() << "Selected File: " << selectedFilePath;
     ui->sendprogressBar->reset();
}
//点击发送文件时，发送
void Widget::sendFileButton()
{
    if (selectedFilePath.isEmpty()) {
        qDebug() << "Please select a file first.";
        return;
    }
    cli->senFile(selectedFilePath);
    int sendCnt = 10;
    //sendCnt是发送的次数，若将其设置成setRange(0,sendCnt)，到达sendCnt时自动计算到100%
    for(int i=0;i<sendCnt;i++){
         ui->sendprogressBar->setRange(0,sendCnt);//最小值和最大值
         ui->sendprogressBar->setValue(i+1);//在循环中，设置当前进度条的运行值
    }
    QDateTime dateTime= QDateTime::currentDateTime();
    QString str = dateTime.toString("yyyy-MM-dd hh:mm:ss");
    QString temp = str + " server\n" + "send a file: "+selectedFilePath;

    ui->messagetextEdit->append(temp);


}
void Widget::conectserver()
{

}

void Widget::updateviewlists()
{
    QStringListModel *listmodel = new QStringListModel(cli->online_people);
    ui->listView->setModel(listmodel);                   //设置模型到listview上

    ui->listView->setMovement(QListView::Free);          //设置数据可以自由拖动
    ui->listView->setSpacing(2);                         //设置数据的间距

}
