#ifndef FRMIPADDRESS_H
#define FRMIPADDRESS_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class frmIPAddress; }
QT_END_NAMESPACE

class frmIPAddress : public QWidget
{
    Q_OBJECT

public:
    frmIPAddress(QWidget *parent = 0);
    ~frmIPAddress();

private slots:
    void on_btnSetIP_clicked();

    void on_btnGetIP_clicked();

    void on_btnClear_clicked();

private:
    Ui::frmIPAddress *ui;
};
#endif // FRMIPADDRESS_H
