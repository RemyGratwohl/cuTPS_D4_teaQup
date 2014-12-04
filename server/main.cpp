#include <QCoreApplication>

#include "Storage/userstoragecontrol.h"
#include "UserManagement/user.h"
#include "ServerCommunication/serverdispatcher.h"
#include "ServerCommunication/messageroutingtypes.h"
#include "../client/ClientCommunication/message.h"
#include "../client/ClientCommunication/errormessage.h"
#include <QDebug>


int main(int argc, char *argv[])
{
    qRegisterMetaType<OBJ_ID_TYPE>("OBJ_ID_TYPE");

    //QCoreApplication a(argc, argv);

    // TEST - USER DB START
    QSharedPointer<UserStorageControl> userAccess;
    userAccess->getUserStorageControl(userAccess);
    qDebug() << "UserAccess Initialized";

    OBJ_ID_TYPE userid = 100945234;
    User* user = new User(userid);

    QString error = "";
    qDebug() << "Before getting user from storage";

    bool Success = userAccess->getUser(userid, user, error);

    qDebug() << Success;

    // TEST - USER DB END

    /* testing start - feel free to comment this stuff out */

    ServerDispatcher* serverDispatcher = new ServerDispatcher(argc, argv);
    serverDispatcher->initialize();

    /* testing end */

    return serverDispatcher->exec();
}
