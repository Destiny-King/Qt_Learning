

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
DESTDIR += $$PWD/bin

SOURCES += \
        main.c \
        soapC.c \
        soapClient.c \
        stdsoap2.c

HEADERS += \
        stdsoap2.h \
        soapStub.h \
        soapH.h \
        MobileCodeWSSoap.nsmap

