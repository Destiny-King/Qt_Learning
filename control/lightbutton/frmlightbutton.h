#ifndef FRMLIGHTBUTTON_H
#define FRMLIGHTBUTTON_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class frmLightButton; }
QT_END_NAMESPACE

class frmLightButton : public QWidget
{
    Q_OBJECT

public:
    frmLightButton(QWidget *parent = 0);
    ~frmLightButton();

private slots:
    void initForm();
    void updateValue();

private:
    Ui::frmLightButton *ui;

    int type;
};
#endif // FRMLIGHTBUTTON_H
