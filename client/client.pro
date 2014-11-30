#-------------------------------------------------
#
# Project created by QtCreator 2014-11-26T10:58:48
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app


SOURCES += main.cpp\
        ClientInterface/mainwindow.cpp \
    ClientCommunication/networklink.cpp \
    ClientCommunication/clientdispatcher.cpp \
    ClientCommunication/message.cpp \
    ClientInterface/viewcontrol.cpp \
    ClientInterface/userauthenticationcontrol.cpp \
    ClientInterface/loginwindow.cpp \
    Shopping/shoppingcartcontrol.cpp \
    Shopping/shoppingcart.cpp \
    Shopping/shoppingcartview.cpp \
    Shopping/billinginfoview.cpp \
    CourseView/courseviewcontrol.cpp \
    CourseView/coursemanagementview.cpp \
    ContentView/contentview.cpp \
    ContentView/contentviewcontrol.cpp \
    UserView/usermanagementview.cpp \
    UserView/userviewcontrol.cpp \
    ../server/ServerCommunication/serializableqobject.cpp \
    ClientCommunication/errormessage.cpp \
    ClientCommunication/datamessage.cpp \
    ../server/UserManagement/user.cpp

HEADERS  += ClientInterface/mainwindow.h \
    ClientCommunication/networklink.h \
    ClientCommunication/clientdispatcher.h \
    ClientCommunication/message.h \
    ClientInterface/viewcontrol.h \
    ClientInterface/userauthenticationcontrol.h \
    ClientInterface/loginwindow.h \
    Shopping/shoppingcartcontrol.h \
    Shopping/shoppingcart.h \
    Shopping/shoppingcartview.h \
    Shopping/billinginfoview.h \
    CourseView/courseviewcontrol.h \
    CourseView/coursemanagementview.h \
    ContentView/contentview.h \
    ContentView/contentviewcontrol.h \
    UserView/usermanagementview.h \
    UserView/userviewcontrol.h \
    ../server/ServerCommunication/serializableqobject.h \
    ../server/ServerCommunication/messageroutingtypes.h \
    ClientCommunication/errormessage.h \
    ClientCommunication/datamessage.h \
    ../server/UserManagement/user.h

FORMS    += ClientInterface/mainwindow.ui \
    ClientInterface/loginwindow.ui \
    Shopping/shoppingcartview.ui \
    Shopping/billinginfoview.ui \
    CourseView/coursemanagementview.ui \
    ContentView/contentview.ui \
    UserView/usermanagementview.ui
