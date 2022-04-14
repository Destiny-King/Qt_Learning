#include "widget.h"
#include "mydialog.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QScrollArea>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    myDialog *d = new myDialog;
    d->exec();
    if(!d->getLoginStatus())
        exit(0);

    lb_name = new QLabel(d->getUserName());
    lcd_time = new QLCDNumber;
    timer = new QTimer;
    timer->start(1000);
    connect(timer,&QTimer::timeout,this,&Widget::displayTime);

    createQuestion();

    QWidget *w = new QWidget;
    QVBoxLayout *vbox = new QVBoxLayout;
    w->setLayout(vbox);
    for (int i = 0; i < questions.length(); i++) {
        vbox->addWidget(questions[i]);
    }
    QScrollArea *sa = new QScrollArea;
    sa->setWidget(w);

    pb_progress = new QProgressBar;
    bt_over = new QPushButton("交卷");
    connect(bt_over,&QPushButton::clicked,this,&Widget::endTest);

    QVBoxLayout *mainbox = new QVBoxLayout;
    mainbox->addWidget(lb_name);
    mainbox->addWidget(lcd_time);
    mainbox->addWidget(sa);
    mainbox->addWidget(pb_progress);
    mainbox->addWidget(bt_over);
    setLayout(mainbox);
}

Widget::~Widget()
{
}

void Widget::createQuestion()
{
    for (int i = 1; i <= 100; i++) {
        choiceQuestion *t = new choiceQuestion;
        t->setQuestion(QString::number(i) + "xxxxxx");
        t->addChoice(QString("A") + "aaaaaa");
        t->addChoice(QString("B") + "bbbbbb");
        t->addChoice(QString("C") + "cccccc");
        t->addChoice(QString("D") + "dddddd");
        questions.append(t);
        questionAnswer.append(-1);
        connect(t,SIGNAL(chosed(int)),this,SLOT(makeChoice(int)));
    }
}

void Widget::makeChoice(int choiceNum)
{
    choiceQuestion *t = static_cast<choiceQuestion *>(sender());
    int questionNum = 0;
    for(;questionNum < questions.length();questionNum++)
        if(t == questions[questionNum])
            break;
    //记录某道题已经做了
    questionAnswer[questionNum] = choiceNum;
    //显示进度
    pb_progress->setValue(questionAnswer.length() - questionAnswer.count(-1));
}

void Widget::endTest()
{
    if(bt_over){
        int ret = QMessageBox::warning(this,"你正在进行交卷操作!","你确定要交卷吗？",QMessageBox::Ok | QMessageBox::Cancel);
        if(ret == QMessageBox::Ok){
            QMessageBox::information(this,"成绩",QString("你做了%0道题").arg(questionAnswer.length() - questionAnswer.count(-1)));
            if(QMessageBox::Ok){
                lcd_time->close();
                this->close();
            }
        }else if(ret == QMessageBox::Cancel){

        }
    }

}

void Widget::displayTime()
{
    static int data = 100;
    lcd_time->display(data--);
    if(data == 0)
        endTest();
}

