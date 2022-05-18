QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    mapwidget.cpp

HEADERS += \
    mainwindow.h \
    mapwidget.h

RESOURCES += \
  res.qrc
