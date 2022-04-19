#ifndef FRMBATTERY_H
#define FRMBATTERY_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class frmBattery; }
QT_END_NAMESPACE

class frmBattery : public QWidget
{
    Q_OBJECT

public:
    frmBattery(QWidget *parent = nullptr);
    ~frmBattery();

private:
    Ui::frmBattery *ui;

private slots:
    void initForm();
};
#endif // FRMBATTERY_H
