QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR += $$PWD/bin

SOURCES += \
    colorwidget.cpp \
    main.cpp \
    frmcolorwidget.cpp

HEADERS += \
    colorwidget.h \
    frmcolorwidget.h

FORMS += \
    frmcolorwidget.ui
