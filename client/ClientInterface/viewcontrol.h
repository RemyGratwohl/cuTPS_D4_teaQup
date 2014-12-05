#ifndef VIEWCONTROL_H
#define VIEWCONTROL_H

/*
* viewcontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* ViewControl class:
* - Top-level control class for the client interface subsystem
* - Responsible for managing the client user interface and other control objects
*
* Traceability: CT-014
*
* Acknowledgements: None
*/

#include <QObject>
#include <QWidget>

#include "loginwindow.h"
#include "mainwindow.h"
#include "userauthenticationcontrol.h"

#include "ContentView/contentviewcontrol.h"
#include "CourseView/courseviewcontrol.h"
#include "Shopping/shoppingcartcontrol.h"

class ViewControl : public QObject
{
    Q_OBJECT

public:
    explicit ViewControl(QObject *parent = 0);

     enum TYPE {CONTENT = 0, COURSE, SHOPPING,BILLING};

     bool changeView(TYPE subsystem);
     bool authenticateUser(OBJ_ID_TYPE id);

     void displayCommunicationError();
     void displayErrorString(QString &err);

     User* getCurrentUser(void) const { return currentUser; }

private:
    User                      *currentUser;  // The User currently logged in

    LoginWindow               *loginWindow;
    MainWindow                *mainWindow;

    UserAuthenticationControl *authenticator;

    /* Subsystem Controllers */
    ContentViewControl        *contentController;
    CourseViewControl         *courseController;
    ShoppingCartControl       *shoppingController;

    bool displayView(QWidget *widget);
    bool changeWindow(QWidget *window);

};

#endif // VIEWCONTROL_H
