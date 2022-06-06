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
  MobileCodeWSSoap.nsmap \
  soapH.h \
  soapStub.h \
  stdsoap2.h
