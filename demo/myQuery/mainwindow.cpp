#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QDebug"
#include "QSqlRecord"
#include "QSqlError"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QSqlQuery query;
    query.prepare("insert into student values(?,?)");

    QVariantList ints;
    ints<<11 <<12<<13<<14;
    query.addBindValue(ints);
    QVariantList names;
    names<<"zs"<<"ls"<<"ww"<<QVariant(QVariant::String);
    query.addBindValue(names);

    if(!query.execBatch())
        qDebug()<<query.lastError();

    //输出整张表
    QSqlQuery query1;
    query1.exec("select * from student");
    while (query1.next()) {
        int id = query1.value(0).toInt();
        QString name = query1.value(1).toString();
        qDebug()<<id <<name;
    }
}
