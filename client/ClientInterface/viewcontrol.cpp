#include "viewcontrol.h"
#include <QMessageBox>

ViewControl::ViewControl(QObject *parent) :
    QObject(parent)
{
    loginWindow = new LoginWindow(this);
    mainWindow  = new MainWindow(this);

    shoppingController = new ShoppingCartControl(this);

    loginWindow->show(); // Show the default window (login)
}

bool ViewControl::authenticateUser(QString username)
{
    if(authenticator->authenticateUser(username, &currentUser))
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
    case(SHOPPING):

        mainWindow->setCentralWidget(shoppingController->getView());
        break;
    case(CONTENT):
        break;
    case(COURSE):
        break;
    default:
        break;
    }
}
