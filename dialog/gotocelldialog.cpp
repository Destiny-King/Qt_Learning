#include "gotocelldialog.h"

GoToCellDialog::GoToCellDialog(QWidget *parent) : QDialog(parent)
{
    setupUi(this);

    //QRegExp类使用正则表达式提供模式匹配
    QRegExp regExp("[A-Za-z][1-9][0-9]{0,2}");
    QRegExpValidator *regExpValidator = new QRegExpValidator(regExp,this);
    lineEdit->setValidator(regExpValidator);

    connect(okButton,SIGNAL(clicked()),this,SLOT(accept()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
}

GoToCellDialog::~GoToCellDialog()
{

}

void GoToCellDialog::on_lineEdit_textChanged()
{
    okButton->setEnabled(lineEdit->hasAcceptableInput());
}
