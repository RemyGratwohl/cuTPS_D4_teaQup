#include "ClientInterface/loginwindow.h"
#include <QApplication>

#include "ClientCommunication/clientdispatcher.h"
#include "ClientCommunication/errormessage.h"
#include "ClientCommunication/message.h"
#include "ClientCommunication/datamessage.h"
#include "../server/ServerCommunication/messageroutingtypes.h"
#include "../server/UserManagement/user.h"
#include <QVector>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /* testing start - feel free to comment this stuff out */
    ClientDispatcher* clientDispatcher = new ClientDispatcher(0,0,0,0,0);
    clientDispatcher->initialize();
    Message* errorMessage = new ErrorMessage(ORDERING, CREATE, new User(), "Client: Hello, Server.");
    clientDispatcher->deliverMsg(errorMessage);
    QVector<SerializableQObject *>* data = new QVector<SerializableQObject *>();
    Message* newMessage = new DataMessage(CONTENT, CREATE, new User(), data);
    //clientDispatcher->deliverMsg(newMessage);

    /* testing end */

    LoginWindow lw;
    lw.show();

    return a.exec();
}
