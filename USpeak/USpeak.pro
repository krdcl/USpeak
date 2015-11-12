#-------------------------------------------------
#
# Project created by QtCreator 2015-11-01T14:21:11
#
#-------------------------------------------------

QT       += core gui websockets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = USpeak
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    account.cpp \
    server.cpp \
    servertcp.cpp \
    clienttcp.cpp

HEADERS  += widget.h \
    includes.h \
    account.h \
    server.h \
    servertcp.h \
    clienttcp.h

FORMS    += widget.ui
