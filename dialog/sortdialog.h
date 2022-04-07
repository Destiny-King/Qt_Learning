#ifndef SORTDIALOG_H
#define SORTDIALOG_H

#include <QDialog>
#include "ui_sortdialog.h"
#include "spreadsheet.h"

class SortDialog : public QDialog,public Ui::SortDialog
{
    Q_OBJECT

public:
    explicit SortDialog(QWidget *parent = 0);

    void setColumnRange(QChar first,QChar last);
    void setSpreadsheet(Spreadsheet *spreadsheet);
    ~SortDialog();

private:

};

#endif // SORTDIALOG_H
