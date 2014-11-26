#-------------------------------------------------
#
# Project created by QtCreator 2014-11-26T10:56:25
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ServerCommunication/serializableqobject.cpp \
    ServerCommunication/serverdispatcher.cpp

HEADERS += \
    ServerCommunication/serializableqobject.h \
    ServerCommunication/serverdispatcher.h \
    ServerCommunication/messageroutingtypes.h \
    ServerCommunication/serializabletypes.h
