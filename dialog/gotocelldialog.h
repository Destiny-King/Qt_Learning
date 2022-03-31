#ifndef GOTOCELLDIALOG_H
#define GOTOCELLDIALOG_H

#include <QDialog>
#include <QRegExpValidator>
#include "ui_gotocelldialog.h"

class GoToCellDialog : public QDialog,public Ui::GoToCellDialog
{
    Q_OBJECT

public:
    GoToCellDialog(QWidget *parent = 0);
    ~GoToCellDialog();

private slots:
    void on_lineEdit_textChanged();

};

#endif // GOTOCELLDIALOG_H
