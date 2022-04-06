#ifndef SORTDIALOG_H
#define SORTDIALOG_H

#include <QDialog>
#include "ui_sortdialog.h"

class SortDialog : public QDialog,public Ui::SortDialog
{
    Q_OBJECT

public:
    explicit SortDialog(QWidget *parent = 0);

    void setColumnRange(QChar first,QChar last);
    ~SortDialog();

private:

};

#endif // SORTDIALOG_H
