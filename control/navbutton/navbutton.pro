QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    iconhelper.cpp \
    main.cpp \
    frmnavbutton.cpp \
    navbutton.cpp

HEADERS += \
    frmnavbutton.h \
    iconhelper.h \
    navbutton.h

FORMS += \
    frmnavbutton.ui

RESOURCES += \
  res.qrc
