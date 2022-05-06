TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$PWD/ffmpeg/include\
               $$PWD/SDL2/include
LIBS += -L$$PWD/ffmpeg/lib -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lpostproc -lswresample -lswscale\
        -L$$PWD/SDL2/lib/x64 -lSDL2

SOURCES += \
        main.cpp \
        packetqueue.cpp

HEADERS += \
  packetqueue.h
