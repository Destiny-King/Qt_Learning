#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QTableWidget>

class Spreadsheet;
class SpreadsheetCompare;

class Spreadsheet : public QTableWidget
{
    Q_OBJECT
public:
    explicit Spreadsheet(QWidget *parent = 0);
    bool autoRecalculate() const{return autoRecalc;}
    void clear();
    QString currentLocation() const;
    QString currenFormula() const;
    QTableWidgetSelectionRange selectedRange() const;
    bool readFile(const QString &fileName);
    bool writeFile(const QString &fileName);
    void sort(const SpreadsheetCompare &compare);

public slots:
    void sut();
    void copy();
    void paste();
    void del();
    void selectCurrentRow();
    void selectCurrentColumn();
    void recalculate();
    void setAutoRecalculate(bool recalc);
    void findNext(const QString &str,Qt::CaseSensitivity cs);

signals:
    void modified();

private slots:
    void somethingChanged();

private:
    enum{MagicNumber = 0x7F51C883,RowCount = 999,ColumnCount = 26};
    QTableWidgetItem *item(int row,int column) const;
    QString text(int row,int column) const;
    QString formula(int row,int column) const;
    void setFormula(int row,int column,const QString &formula);
    bool autoRecalc;

};

class SpreadsheetCompare{
    bool operator()(const QStringList &row1,const QStringList &row2) const;
    enum{KeyCount = 3};
    int keys[KeyCount];
    bool ascending[KeyCount];
};

#endif // SPREADSHEET_H
