#include "spreadsheet.h"

Spreadsheet::Spreadsheet(QWidget *parent) : QTableWidget(parent)
{
    autoRecalc = true;
    setItemPrototype(new QTableWidgetItem);
    setSelectionMode(ContiguousSelection);
    connect(this,SIGNAL(itemChanged(QTableWidgetItem *)),this,SLOT(somethingChanged()));
    clear();
}

void Spreadsheet::clear()
{
    setRowCount(0);
    setColumnCount(0);
    setRowCount(RowCount);
    setColumnCount(ColumnCount);

    for (int i = 0; i < ColumnCount; ++i) {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(QString(QChar('A' + i)));
        setHorizontalHeaderItem(i,item);
    }
    setCurrentCell(0,0);
}



bool Spreadsheet::readFile(const QString &fileName)
{

}

bool Spreadsheet::writeFile(const QString &fileName)
{

}

QTableWidgetItem *Spreadsheet::item(int row, int column) const
{
    return static_cast<QTableWidgetItem *>(item(row,column));
}

QString Spreadsheet::text(int row, int column) const
{

}
