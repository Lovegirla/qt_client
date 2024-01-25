#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    int flag = 0;
    explicit login(QWidget *parent = nullptr);
    ~login();
    QString getusername();
    QString getip();
private:
    Ui::login *ui;
private slots:
    void gotowid();
    void onLoginClicked();

signals:
    void loginSuccessful();

};

#endif // LOGIN_H
