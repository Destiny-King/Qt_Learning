#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class myDialog : public QDialog
{
public:
    myDialog(QWidget *parent = 0,Qt::WindowFlags f = Qt::WindowFlags());

    bool getLoginStatus()    const;
    QString getUserName()    const;

private slots:
    void login();

private:
    QLabel *lb_logo;
    QLineEdit *le_username;
    QLineEdit *le_password;
    QPushButton *bt_login;

    bool loginSuccessed;

};

#endif // MYDIALOG_H
