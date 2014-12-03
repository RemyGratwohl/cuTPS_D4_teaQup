#include "ClientInterface/loginwindow.h"
#include <QApplication>

#include "ClientCommunication/clientdispatcher.h"
#include "ClientCommunication/errormessage.h"
#include "ClientCommunication/message.h"
#include "../server/ServerCommunication/messageroutingtypes.h"
#include "../server/UserManagement/user.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /* testing start - feel free to comment this stuff out */
    ClientDispatcher* clientDispatcher = new ClientDispatcher(0,0,0,0,0);
    clientDispatcher->initialize();
    Message* errorMessage = new ErrorMessage(CONTENT, CREATE, new User(), "Client: Hello, Server.");
    clientDispatcher->deliverMsg(errorMessage);

    /* testing end */

    LoginWindow lw;
    lw.show();

    return a.exec();
}
