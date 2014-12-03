#-------------------------------------------------
#
# Project created by QtCreator 2014-11-26T10:56:25
#
#-------------------------------------------------

QT       += core
QT       += network
QT       += sql

QT       -= gui

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ServerCommunication/serializableqobject.cpp \
    ServerCommunication/serverdispatcher.cpp \
    ../client/ClientCommunication/message.cpp \
    UserManagement/user.cpp \
    Purchasing/ordercontrol.cpp \
    CourseManagement/coursecontrol.cpp \
    Storage/contentstoragecontrol.cpp \
    ContentManagement/contentcontrol.cpp \
    UserManagement/usercontrol.cpp \
    UserManagement/userauthenticationservercontrol.cpp \
    Storage/orderstoragecontrol.cpp \
    Storage/mainstoragecontrol.cpp \
    Storage/userstoragecontrol.cpp \
    Storage/coursestoragecontrol.cpp \
    CourseManagement/course.cpp \
    CourseManagement/term.cpp \
    ContentManagement/contentitem.cpp \
    Purchasing/order.cpp \
    Purchasing/billinginformation.cpp \
    ContentManagement/book.cpp \
    ContentManagement/chapter.cpp \
    ContentManagement/chaptersection.cpp \
    ContentManagement/purchasingdetails.cpp \
    ServerCommunication/networklink.cpp \
    ../client/ClientCommunication/errormessage.cpp \
    ../client/ClientCommunication/datamessage.cpp

HEADERS += \
    ServerCommunication/serializableqobject.h \
    ServerCommunication/serverdispatcher.h \
    ServerCommunication/messageroutingtypes.h \
    ServerCommunication/serializabletypes.h \
    ../client/ClientCommunication/message.h \
    UserManagement/user.h \
    Purchasing/ordercontrol.h \
    CourseManagement/coursecontrol.h \
    Storage/contentstoragecontrol.h \
    ContentManagement/contentcontrol.h \
    UserManagement/usercontrol.h \
    UserManagement/userauthenticationservercontrol.h \
    Storage/orderstoragecontrol.h \
    Storage/mainstoragecontrol.h \
    Storage/userstoragecontrol.h \
    Storage/coursestoragecontrol.h \
    CourseManagement/course.h \
    CourseManagement/term.h \
    ContentManagement/contentitem.h \
    Purchasing/order.h \
    Purchasing/billinginformation.h \
    ContentManagement/book.h \
    ContentManagement/chapter.h \
    ContentManagement/chaptersection.h \
    ContentManagement/purchasingdetails.h \
    ServerCommunication/networklink.h \
    ServerCommunication/serializableobjectfactory.h \
    ../client/ClientCommunication/errormessage.h \
    ../client/ClientCommunication/datamessage.h
