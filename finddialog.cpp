#include "finddialog.h"
#include "ui_finddialog.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "qcheckbox.h"
#include "qpushbutton.h"
#include "QHBoxLayout"
#include "QVBoxLayout"

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent)
{
    label = new QLabel(tr("Find &what:"));
    lineEdit = new QLineEdit;
    //buddy就是一个窗口部件，它可以在按下标签的快捷键时接收焦点。
    label->setBuddy(lineEdit);

    caseCheckBox = new QCheckBox(tr("Match &case"));
    backwardCheckBox = new QCheckBox(tr("Search &backward"));

    findButton = new QPushButton(tr("&Find"));
    //setDefault(true)让按钮成为对话框的默认按钮，当用户按下Enter键时能够按下对应的按钮。
    findButton->setDefault(true);
    findButton->setEnabled(false);

    closeButton = new QPushButton(tr("Close"));

    connect(lineEdit,SIGNAL(textChanged(const QString &)),this,SLOT(enableFindButton(const QString &)));
    connect(findButton,SIGNAL(clicked()),this,SLOT(findClicked()));
    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));

    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(label);
    topLeftLayout->addWidget(lineEdit);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addWidget(caseCheckBox);
    leftLayout->addWidget(backwardCheckBox);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(findButton);
    rightLayout->addWidget(closeButton);
    rightLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);
}

FindDialog::~FindDialog()
{

}

void FindDialog::findClicked()
{
    QString text = lineEdit->text();
    //三目运算符
    Qt::CaseSensitivity cs = caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    if(backwardCheckBox->isChecked()){
        //当值改变时发射信号，让执行槽函数。
        emit findPrevious(text,cs);
    }else {
        emit findNext(text,cs);
    }
}

void FindDialog::enableFindButton(const QString &text)
{
    if(text.isEmpty()){
        findButton->setEnabled(false);
    }else{
        findButton->setEnabled(true);
    }
}
