TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

INCLUDEPATH += $$PWD/include
LIBS += -L$$PWD/lib/x64 -lSDL2 -lSDL2main -lSDL2test

