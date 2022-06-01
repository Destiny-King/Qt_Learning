#include "frmcolorwidget.h"

#include "colorwidget.h"
#include "ui_frmcolorwidget.h"

frmColorWidget::frmColorWidget(QWidget* parent) : QWidget(parent), ui(new Ui::frmColorWidget) { ui->setupUi(this); }

frmColorWidget::~frmColorWidget() { delete ui; }

void frmColorWidget::on_pushButton_clicked() {
    ColorWidget::Instance()->show();
    //显示取色界面
}
