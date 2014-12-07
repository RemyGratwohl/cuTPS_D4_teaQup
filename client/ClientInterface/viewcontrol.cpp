#include "viewcontrol.h"
#include <QMessageBox>
#include <QDebug>
#include "../server/ServerCommunication/messageroutingtypes.h"
#include "../server/ContentManagement/book.h"
#include "../server/ContentManagement/chapter.h"
#include "userauthenticationcontrol.h"
#include "../ContentView/contentviewcontrol.h"
#include "../CourseView/courseviewcontrol.h"
#include "../Shopping/shoppingcartcontrol.h"

ViewControl::ViewControl(void) :
    QObject(), currentUser(0), loginWindow(0), mainWindow(0),
    authenticator(0), clientDispatcher(0),
    contentController(0), courseController(0), shoppingController(0)
{
    loginWindow = new LoginWindow(this);
    mainWindow  = new MainWindow(this);

    clientDispatcher = new ClientDispatcher(this, this);
    clientDispatcher->initialize();

    authenticator = new UserAuthenticationControl(this, clientDispatcher);

    loginWindow->show(); // Show the initial window (login)
}

bool ViewControl::initialize(void) {
    if( !clientDispatcher->initialize() ) {
        QString error = "Networking could not be initialized, regardless of whether the server is available."
                " The application will now exit.";
        displayErrorString(error);
        return false;
    }
    return true;
}

void ViewControl::setShoppingList(QVector<ContentItem *>* list)
{
    shoppingController->handleShoppingList(list);
}

bool ViewControl::processMsg(Message *msg)
{
    /* Display all error messages
     * (In a real application, we wouldn't do this
     *  at such a coarse level of detail, as it may sometimes
     *  inform the user of bugs, depending on the usage of error messages.)
     */
    const ErrorMessage* errorMsg = qobject_cast<const ErrorMessage*>(msg);
    if( errorMsg != 0 ) {
        QString error = errorMsg->getError();
        displayErrorString(error);
        return true;
    }

    DEST_TYPE msgDest = msg->getDestType();

    switch(msgDest)
    {
    case ORDERING:
        // orderControl handles message
        return shoppingController->processMsg(msg);
        break;
    case USER:
        // user auth
        return authenticator->processMsg(msg);
        break;
    case CONTENT:
        // contentControl handles message
        return contentController->processMsg(msg);
        break;
    case COURSE:
        // courseControl handles message
        return courseController->processMsg(msg);
        break;
    default:
        qDebug() << "ViewControl::processMsg() : Unknown message destination.";
        return false;
    }

    return false;
}

void ViewControl::requestAuthentication(OBJ_ID_TYPE id)
{
    authenticator->requestAuthentication(id);
}

void ViewControl::displayCommunicationError()
{
    QString commErr = "Unable to Communicate with the Server";
    displayErrorString(commErr);
}

void ViewControl::displayErrorString(QString &err)
{
    QMessageBox msgBox;
    msgBox.setText(err);
    qDebug() << err;
    msgBox.exec(); // Note: This blocks the GUI until the user acknowledges the error.
}

bool ViewControl::changeView(TYPE subsystem)
{

    switch(subsystem)
    {
    case(SHOPPING_VIEW):
        mainWindow->addView(shoppingController->getView());
        break;
    case(CONTENT_VIEW):
        mainWindow->addView(contentController->getView());
        break;
    case(COURSE_VIEW):
        mainWindow->addView(courseController->getView());
        break;
    default:
        qDebug() << "ViewControl : Error - Unknown subsystem view type.";
        return false;
    }

    return true;
}

bool ViewControl::closeView()
{
    mainWindow->popView();
    return true;
}

bool ViewControl::setCurrentUser(User* user) {
    if( currentUser == 0 ) {
       currentUser = user;
       currentUser->setParent(this);

       loginWindow->hide();
       mainWindow->show();

       if(currentUser->getType() == User::STUDENT)
       {
           shoppingController = new ShoppingCartControl(this,clientDispatcher);
           contentController = new ContentViewControl(this, clientDispatcher);
           studentView        = new StudentView(this);
           mainWindow->addView(studentView);
       }else if(currentUser->getType() == User::CONTENTMGR)
       {
           contentController = new ContentViewControl(this, clientDispatcher);
           courseController = new CourseViewControl(this, clientDispatcher);
           changeView(CONTENT_VIEW);
       }else if (currentUser ->getType() == User::ADMIN)
       {
           qDebug() << "Admin View Not implemented";
       }else{
           qDebug() << "Invalid User Type Detected";
           return false;
       }

       return true;
    } else {
        qDebug() << "ViewControl : Error - Current user has already been set.";
        return false;
    }
}
