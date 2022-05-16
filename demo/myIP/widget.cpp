#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

//    QString localHostName = QHostInfo::localHostName();
//    qDebug() << "localHostName：" << localHostName;

//    QHostInfo info = QHostInfo::fromName(localHostName);
//    qDebug() << "IP Address：" << info.addresses();

//    foreach(QHostAddress address,info.addresses()){
//        if(address.protocol()==QAbstractSocket::IPv4Protocol)
//            qDebug() << address.toString();
//    }

    QHostInfo::lookupHost("www.qter.org",this,SLOT(lookedup(QHostInfo)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::lookedup(const QHostInfo &host)
{
    qDebug() << host.addresses().first().toString();
}

