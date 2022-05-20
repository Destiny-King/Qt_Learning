#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //点击选取文件按钮，弹出文件对话框
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        QString path=QFileDialog::getOpenFileName(this,"打开文件","E:\\Program\\CLion\\Qt\\MyPaintDevice\\image");
        ui->lineEdit->setText(path);

        QFile file(path);
        file.open(QIODevice::ReadOnly);
        QByteArray array=file.readAll();
        ui->textEdit->setText(array);

        file.close();

        //写入文件 追加方式写文件
        file.open(QIODevice::Append);
        file.write("写文件");
        file.close();

        QFileInfo info(path);
        qDebug() <<"大小"<<info.size()<<"后缀名"<<info.suffix()<<"文件名称"<<info.fileName()<<"文件路径"<<info.filePath();

    });
}

Widget::~Widget()
{
    delete ui;
}
