#include "mydialog.h"
#include <QVBoxLayout>
#include <QMessageBox>

myDialog::myDialog(QWidget *parent, Qt::WindowFlags f) : QDialog(parent,f)
{
    loginSuccessed = false;

    lb_logo = new QLabel("欢迎");
    lb_logo->setAlignment(Qt::AlignCenter);

    le_username = new QLineEdit;
    //显示提示信息
    le_username->setPlaceholderText("用户名");
    le_password = new QLineEdit;
    //显示提示信息
    le_password->setPlaceholderText("密码");
    le_password->setEchoMode(QLineEdit::Password);

    bt_login = new QPushButton("登录");

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(lb_logo);
    vbox->addWidget(le_username);
    vbox->addWidget(le_password);
    vbox->addWidget(bt_login);
    setLayout(vbox);

    connect(bt_login,&QPushButton::clicked,this,&myDialog::login);
}

void myDialog::login()
{
    if(!le_password->text().isEmpty() && le_password->text() == le_username->text()){
        loginSuccessed = true;
        close();
    }else{
        QMessageBox::warning(this,"登录异常","用户名或密码错误");
    }
}

bool myDialog::getLoginStatus() const
{
    return loginSuccessed;
}

QString myDialog::getUserName() const
{
    return  le_username->text();
}
