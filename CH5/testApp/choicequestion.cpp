#include "choicequestion.h"

choiceQuestion::choiceQuestion(QWidget *parent) : QWidget(parent)
{
    lb_pix = new QLabel;
    lb_pix->setMaximumSize(200,100);
    //确定标签是否会缩放其内容以填充所有可用空间
    lb_pix->setScaledContents(true);
    choice.clear();

    gb = new QGroupBox;
    gb->setMinimumWidth(640);
    gb_vbox = new QVBoxLayout;
    gb_vbox->addWidget(lb_pix);
    gb->setLayout(gb_vbox);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(gb);
    setLayout(vbox);
}

void choiceQuestion::choiceClicked(bool x)
{
    //提取选项
    QRadioButton *t = static_cast<QRadioButton *>(sender());

    //换算下表
    for (int index = 0; index < choice.length(); index++) {
        if(t == choice[index]){
            emit chosed(index);
            break;
        }
    }
}

//设置题目内容
void choiceQuestion::setQuestion(QString Question)
{
    gb->setTitle(Question);
}

void choiceQuestion::addChoice(QString Choice)
{
    QRadioButton *t = new QRadioButton(Choice);
    choice.append(t);
    gb_vbox->addWidget(t);
    connect(t,SIGNAL(clicked(bool)),this,SLOT(choiceClicked(bool)));
}

void choiceQuestion::setPix(QString filename)
{
    lb_pix->setPixmap(QPixmap(filename));
}
