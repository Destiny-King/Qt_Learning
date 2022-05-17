QT       += core gui texttospeech

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR += $$PWD/bin

SOURCES += \
    main.cpp \
    mythread.cpp \
    threadtest.cpp \
    widget.cpp

HEADERS += \
    mythread.h \
    threadtest.h \
    widget.h

FORMS += \
    threadtest.ui \
    widget.ui
