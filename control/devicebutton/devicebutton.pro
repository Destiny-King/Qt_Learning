QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    devicebutton.cpp \
    main.cpp \
    frmdevicebutton.cpp

HEADERS += \
    devicebutton.h \
    frmdevicebutton.h

FORMS += \
    frmdevicebutton.ui

RESOURCES += \
  res.qrc
