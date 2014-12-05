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
    ../server/ServerCommunication/serializableqobject.cpp \
    ClientCommunication/errormessage.cpp \
    ClientCommunication/datamessage.cpp \
    ../server/UserManagement/user.cpp \
    ../server/ContentManagement/purchasingdetails.cpp \
    ../server/ContentManagement/contentitem.cpp \
    ../server/ContentManagement/chaptersection.cpp \
    ../server/ContentManagement/chapter.cpp \
    ../server/ContentManagement/book.cpp \
    ../server/Purchasing/order.cpp \
    ../server/Purchasing/billinginformation.cpp \
    ../server/CourseManagement/term.cpp \
    ../server/CourseManagement/course.cpp \
    ClientCommunication/successmessage.cpp \
    util/abstractviewcontroller.cpp

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
    ../server/ServerCommunication/serializableqobject.h \
    ../server/ServerCommunication/messageroutingtypes.h \
    ClientCommunication/errormessage.h \
    ClientCommunication/datamessage.h \
    ../server/UserManagement/user.h \
    ../server/ServerCommunication/serializabletypes.h \
    ../server/ServerCommunication/serializableobjectfactory.h \
    ../server/ContentManagement/purchasingdetails.h \
    ../server/ContentManagement/contentitem.h \
    ../server/ContentManagement/chaptersection.h \
    ../server/ContentManagement/chapter.h \
    ../server/ContentManagement/book.h \
    ../server/Purchasing/order.h \
    ../server/Purchasing/billinginformation.h \
    ../server/CourseManagement/term.h \
    ../server/CourseManagement/course.h \
    ClientCommunication/successmessage.h \
    util/abstractviewcontroller.h

FORMS    += ClientInterface/mainwindow.ui \
    ClientInterface/loginwindow.ui \
    Shopping/shoppingcartview.ui \
    Shopping/billinginfoview.ui \
    CourseView/coursemanagementview.ui \
    ContentView/contentview.ui
