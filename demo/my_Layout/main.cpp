#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    w.setWindowTitle("Enter your age");
    QSpinBox *spinBox = new QSpinBox(&w);
    QSlider *slider = new QSlider(Qt::Horizontal,&w);
    spinBox->setRange(0,130);
    slider->setRange(0,130);

    QObject::connect(slider,&QSlider::valueChanged,spinBox,&QSpinBox::setValue);
    void (QSpinBox::*spinBoxSignal)(int) = &QSpinBox::valueChanged;
    QObject::connect(spinBox,spinBoxSignal,slider,&QSlider::setValue);
    spinBox->setValue(35);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(spinBox);
    layout->addWidget(slider);
    w.setLayout(layout);

    w.show();
    return a.exec();
}
