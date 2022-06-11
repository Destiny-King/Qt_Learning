QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR += $$PWD/bin

SOURCES += \
    jsonmain.cpp \
    main.cpp \
    frmmain.cpp

HEADERS += \
    frmmain.h \
    jsonmain.h

FORMS += \
    frmmain.ui \
    jsonmain.ui
