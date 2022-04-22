QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    imageswitch.cpp \
    main.cpp \
    frmimageswitch.cpp

HEADERS += \
    frmimageswitch.h \
    imageswitch.h

FORMS += \
    frmimageswitch.ui

RESOURCES += \
  res.qrc
