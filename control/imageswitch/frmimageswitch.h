#ifndef FRMIMAGESWITCH_H
#define FRMIMAGESWITCH_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class frmImageSwitch; }
QT_END_NAMESPACE

class frmImageSwitch : public QWidget
{
    Q_OBJECT

public:
    frmImageSwitch(QWidget *parent = 0);
    ~frmImageSwitch();

private:
    Ui::frmImageSwitch *ui;

private slots:
    void initForm();
};
#endif // FRMIMAGESWITCH_H
