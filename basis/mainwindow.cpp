#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    spinBox = new QSpinBox;
    spinBox->setMaximumWidth(60);
    slider = new QSlider(Qt::Horizontal);
    spinBox->setRange(0,130);
    slider->setRange(0,130);

    connect(spinBox,SIGNAL(valueChanged(int)),slider,SLOT(setValue(int)));
    connect(slider,SIGNAL(valueChanged(int)),spinBox,SLOT(setValue(int)));
    spinBox->setValue(35);

    hBoxLayout = new QHBoxLayout();
    hBoxLayout->addWidget(spinBox);
    hBoxLayout->addWidget(slider);

    hWidget = new QWidget;
    hWidget->setLayout(hBoxLayout);
    hWidget->setParent(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

