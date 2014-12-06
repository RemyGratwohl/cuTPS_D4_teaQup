#include "viewcontrol.h"
#include <QMessageBox>
#include "../server/ServerCommunication/messageroutingtypes.h"

ViewControl::ViewControl(QObject *parent) :
    QObject(parent)
{
    loginWindow = new LoginWindow(this);
    mainWindow  = new MainWindow(this);

    shoppingController = new ShoppingCartControl(this);

    clientDispatcher = new ClientDispatcher(this, this);
    clientDispatcher->initialize();

    loginWindow->show(); // Show the default window (login)
}

bool ViewControl::begin()
{
    QVector<SerializableQObject *>* data = new QVector<SerializableQObject *>();
    Message* newMessage = new DataMessage(ORDERING, UPDATE, new User((quint64)25), data);
    clientDispatcher->deliverMsg(newMessage);

    return true;
}

bool ViewControl::processMsg(Message *msg)
{
    DEST_TYPE msgDest = msg->getDestType();

    switch(msgDest)
    {
    case ORDERING:
        // orderControl handles message
        return shoppingController->processMsg(msg);
        break;
    case USER:
        // user auth
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
        return false;
        break;
    }

    return false;
}

bool ViewControl::authenticateUser(OBJ_ID_TYPE id)
{
    if(authenticator->authenticateUser(id, &currentUser))
    {
        loginWindow->hide();
        mainWindow->show();
        return true;
    }

    return false;
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
    msgBox.exec();
}

bool ViewControl::changeView(TYPE subsystem){

    switch(subsystem)
    {
    case(SHOPPING_VIEW):
        mainWindow->setCentralWidget(shoppingController->getView());
        break;
    case(CONTENT_VIEW):
        mainWindow->setCentralWidget(contentController->getView());
        break;
    case(COURSE_VIEW):
        break;
    default:
        break;
    }

    return true;
}
