#include "login.h"
#include "ui_login.h"
#include "widget.h"
login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onLoginClicked()));
}

login::~login()
{
    delete ui;
}
void login::gotowid()
{
    flag =1;
}
void login::onLoginClicked()
{
    loginSuccessful();
}

QString login::getusername()
{
    return ui->lineEdit->text();
}
QString login::getip()
{
    return ui->lineEdit_2->text();
}
