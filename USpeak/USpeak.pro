#-------------------------------------------------
#
# Project created by QtCreator 2015-11-01T14:21:11
#
#-------------------------------------------------

QT       += core gui websockets network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = USpeak
TEMPLATE = app
#blabla

SOURCES += main.cpp\
        widget.cpp \
    account.cpp \
    server.cpp \
    servertcp.cpp \
    clienttcp.cpp \
    audiorecorder.cpp \
    audiodecoder.cpp

HEADERS  += widget.h \
    includes.h \
    account.h \
    server.h \
    servertcp.h \
    clienttcp.h \
    audiorecorder.h \
    audiodecoder.h

FORMS    += widget.ui
