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

#include "studentview.h"
#include "ClientCommunication/clientdispatcher.h"

class UserAuthenticationControl;
class CourseViewControl;
class ContentViewControl;
class ShoppingCartControl;

class ViewControl : public QObject
{
    Q_OBJECT
public:
    /* Enumerates the subsystems that have views which can
     * be displayed through the ViewControl object.
     */
     enum TYPE {CONTENT_VIEW = 0, COURSE_VIEW, SHOPPING_VIEW, BILLING_VIEW};

     /* Constructor
      *   Initializes client process control flow
      */
     ViewControl(void);

     /* Member Function: initialize()
      *   Attempts to initialize the ClientDispatcher object,
      *   and returns false in case of failure.
      */
     bool initialize(void);

     // temp func to send messages to server
     bool begin();

     /* Member Function: processMsg
      *   Handles a message received from the dispatcher.
      *   If the message is an error message, it displays
      *     the error using displayErrorString().
      *   If the message is a data message, it forwards
      *     it to the appropriate subsystem
      *     (or to the UserAuthenticationControl object, but this happens rarely)
      * in: Message to be processed
      * Side Effects: None
      * Return Value: True, if the operation succeeded.
      */
     virtual bool processMsg(Message* msg);

     /* Member Function: changeView
      *   Used by another subsystem to ask for the view of some
      *   other subsystem to be shown.
      * in: Subsystem whose view is to be displayed
      * Side Effects: None
      * Return Value: True, if the operation succeeded
      *   (e.g. the input argument is valid)
      */
     bool changeView(TYPE subsystem);

     /* Member Function: closeView()
      *   Closes the top level view by means of popping it off the widget stack
      * in: None
      * Side Effects: None
      * Return Value: True, if the operation succeeded.
      */
     bool closeView();
     bool authenticateUser(OBJ_ID_TYPE id);

     /* Member Function: requestAuthentication
      *   To be called by the login window
      *     when the user inputs their ID number
      *     to use for login
      * in: User ID
      * Side Effects: None
      * Return Value: None
      */
     void requestAuthentication(OBJ_ID_TYPE id);

     /* Member Function: displayCommunicationError
      *   Notifies the user that there is a problem
      *     communicating with the server.
      * Side Effects: None
      * Return Value: None
      */
     void displayCommunicationError(void);

     /* Member Function: displayErrorString
      *   Notifies the user of an error.
      *   Also logs the message using qDebug().
      * in: Error message to be displayed
      * Side Effects: None
      * Return Value: None
      */
     void displayErrorString(QString &err);

     /* Used by other subsystems to send messages to the server. */
     User* getCurrentUser(void) const { return currentUser; }

     /* Member Function: setCurrentUser
      *   Called by the UserAuthenticationControl object
      *     when a user is authenticated.
      *   Currently, this function does not allow
      *     a new user to be set when this object's
      *     current user is non-null, as the system
      *     does not have the functionality necessary for switching
      *     users.
      * in: User credentials
      * Side Effects: None
      * Return Value: True, if the new credentials are now in use.
      *               False, if the current user was not null.
      */
     bool setCurrentUser(User* user);

     void setShoppingList(QVector<ContentItem*>* list);

     // Helper functions
private:
     bool displayView(QWidget *widget);
     bool changeWindow(QWidget *window);

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
};

#endif // VIEWCONTROL_H
