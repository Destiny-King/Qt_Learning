#include "widget.h"
#include "ui_widget.h"
#include <QGridLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //2.构造所需控件
    QFont font("Times",30,QFont::Bold);
    this->setFont(font);

    le = new QLineEdit("0");
    le->setAlignment(Qt::AlignRight);
    le->setFixedHeight(100);
    le->setReadOnly(true);
    QStringList l = {"0","1","2","3","4","5","6","7","8","9",".","+","-","*","/","<-","C","="};
    for (int i = 0; i < l.length(); i++) {
        pb[i] = new QPushButton(l.at(i));
    }
    pb[17]->setFixedHeight(120);

    //3.做必要的排版
    QGridLayout *gbox = new QGridLayout;
    gbox->addWidget(le,0,0,1,5);

    gbox->addWidget(pb[7], 1, 0, 1, 1);
    gbox->addWidget(pb[8], 1, 1, 1, 1);
    gbox->addWidget(pb[9], 1, 2, 1, 1);
    gbox->addWidget(pb[14], 1, 3, 1, 1);
    gbox->addWidget(pb[16], 1, 4, 1, 1);

    gbox->addWidget(pb[4], 2, 0, 1, 1);
    gbox->addWidget(pb[5], 2, 1, 1, 1);
    gbox->addWidget(pb[6], 2, 2, 1, 1);
    gbox->addWidget(pb[13], 2, 3, 1, 1);
    gbox->addWidget(pb[15], 2, 4, 1, 1);

    gbox->addWidget(pb[1], 3, 0, 1, 1);
    gbox->addWidget(pb[2], 3, 1, 1, 1);
    gbox->addWidget(pb[3], 3, 2, 1, 1);
    gbox->addWidget(pb[12], 3, 3, 1, 1);
    gbox->addWidget(pb[17], 3, 4, 2, 1);

    gbox->addWidget(pb[0], 4, 0, 1, 1);
    gbox->addWidget(pb[10], 4, 1, 1, 2);
    gbox->addWidget(pb[11], 4, 3, 1, 1);

    setLayout(gbox);

    //参数初始化
    num1 = num2 = 0;
    expr = '#';
    //4.连接信号和槽
    for (int i = 0; i < 10; i++)
        connect(pb[i],SIGNAL(clicked(bool)),this,SLOT(num_clicked()));
    for (int i = 11; i < 15; i++)
    connect(pb[i],SIGNAL(clicked(bool)),this,SLOT(expr_clicked()));
    connect(pb[10],SIGNAL(clicked(bool)),this,SLOT(point_clicked()));
    connect(pb[15],SIGNAL(clicked(bool)),this,SLOT(chop_clicked()));
    connect(pb[16],SIGNAL(clicked(bool)),this,SLOT(clear_clicked()));
    connect(pb[17],SIGNAL(clicked(bool)),this,SLOT(eql_clicked()));
}

Widget::~Widget()
{
    delete ui;
}

//5.槽函数实现
//0~9
void Widget::num_clicked()
{
    //转换成按钮
    QPushButton *pb_num = dynamic_cast<QPushButton *>(sender());
    QString str = pb_num->text();
    QString lestr = le->text();
    if(lestr == "0"){
        le->setText(str);
        return;
    }
    lestr += str;
    le->setText(lestr);
}

//+-*/
void Widget::expr_clicked()
{
    if(expr != '#')
        return;
    num1 = le->text().toDouble();
    QPushButton *pb_expr = dynamic_cast<QPushButton *>(sender());
    //以QByteArray的形式返回字符串
    expr = pb_expr->text().at(0).toLatin1();
    le->setText("0");
}

//.
void Widget::point_clicked()
{
    QString str = le->text();
    //分割字符串
    QStringList l1 = str.split(".");
    //判断分割后字符串的个数
    if(l1.length() > 1){
        return;
    }
    str += ".";
    le->setText(str);
}

//<-
void Widget::chop_clicked()
{
    QString str = le->text();
    if(str.length() == 1){
        le->setText("0");
        return;
    }
    //删除最后一个元素
    str.chop(1);
    le->setText(str);
}

//clear
void Widget::clear_clicked()
{
    le->setText("0");
}

void Widget::eql_clicked()
{
    if(expr == '#')
        return;
    num2 = le->text().toDouble();
    if('+' == expr)
        num = num1 + num2;
    else if('-' == expr)
        num = num1 - num2;
    else if('*' == expr)
        num = num1 * num2;
    else{
        if(num2 == 0){
            le->setText("Divisor isn't zero");
            num1 = num2 = 0;
            expr = '#';
            return;
        }
        num = num1 / num2;
    }
    le->setText(QString::number(num));
    num1 = num2 = 0;
    expr = '#';
}


