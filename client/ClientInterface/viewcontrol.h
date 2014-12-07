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

#include "studentview.h"
#include "ClientCommunication/clientdispatcher.h"

#include "ContentView/contentviewcontrol.h"
#include "CourseView/courseviewcontrol.h"
#include "Shopping/shoppingcartcontrol.h"

class ViewControl : public QObject
{
    Q_OBJECT

public:
    explicit ViewControl(QObject *parent = 0);

     enum TYPE {CONTENT_VIEW = 0, COURSE_VIEW, SHOPPING_VIEW, BILLING_VIEW};

     // temp func to send messages to server
     bool begin();

     /* Member Function: processMsg
      *   Handles a message received from the dispatcher,
      *     possibly resulting in messages sent back through the dispatcher
      * in: Message to be processed
      * Side Effects: None
      * Return Value: True, if the operation succeeded.
      */
     virtual bool processMsg(Message* msg);

     bool changeView(TYPE subsystem);

     /* Member Function: closeView()
      *   Closes the top level view by means of popping it off the widget stack
      * in: None
      * Side Effects: None
      * Return Value: True, if the operation succeeded.
      */
     bool closeView();
     bool authenticateUser(OBJ_ID_TYPE id);

     void displayCommunicationError();
     void displayErrorString(QString &err);

     void setShoppingList(QVector<SerializableQObject *>* list);

private:
    User                      *currentUser;  // The User currently logged in

    LoginWindow               *loginWindow;
    MainWindow                *mainWindow;
    StudentView               *studentView;

    UserAuthenticationControl *authenticator;

    /* Subsystem Controllers */
    ClientDispatcher          *clientDispatcher;
    ContentViewControl        *contentController;
    CourseViewControl         *courseController;
    ShoppingCartControl       *shoppingController;

    bool displayView(QWidget *widget);
    bool changeWindow(QWidget *window);

};

#endif // VIEWCONTROL_H
