#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(&myProcess,SIGNAL(readyRead()),this,SLOT(showResult()));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    QString program = "cmd.exe";
    QStringList arguments;
    arguments<<"/c dir&pause";
    myProcess.start(program,arguments);

}

void Widget::showResult()
{
    qDebug() << "showResult:" << endl
             <<QString(myProcess.readAll());
}
