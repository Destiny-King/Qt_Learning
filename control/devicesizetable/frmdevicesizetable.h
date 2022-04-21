#ifndef FRMDEVICESIZETABLE_H
#define FRMDEVICESIZETABLE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class frmDeviceSizeTable; }
QT_END_NAMESPACE

class frmDeviceSizeTable : public QWidget
{
    Q_OBJECT

public:
    frmDeviceSizeTable(QWidget *parent = 0);
    ~frmDeviceSizeTable();

private:
    Ui::frmDeviceSizeTable *ui;
};
#endif // FRMDEVICESIZETABLE_H
