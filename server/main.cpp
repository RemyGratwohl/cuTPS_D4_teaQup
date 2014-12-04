#include <QCoreApplication>

#include "Storage/mainstoragecontrol.h"
#include "ServerCommunication/serverdispatcher.h"
#include "ServerCommunication/messageroutingtypes.h"
#include "../client/ClientCommunication/message.h"
#include "../client/ClientCommunication/errormessage.h"


int main(int argc, char *argv[])
{
    qRegisterMetaType<OBJ_ID_TYPE>("OBJ_ID_TYPE");

    //QCoreApplication a(argc, argv);

    /* testing start - feel free to comment this stuff out */

    ServerDispatcher* serverDispatcher = new ServerDispatcher(argc, argv);
    serverDispatcher->initialize();

    /* testing end */

    return serverDispatcher->exec();
}
