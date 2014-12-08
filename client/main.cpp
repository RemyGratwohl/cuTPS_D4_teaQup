#include <QApplication>
#include "ClientInterface/viewcontrol.h"

#include "ClientCommunication/clientdispatcher.h"
#include "ClientCommunication/errormessage.h"
#include "ClientCommunication/message.h"
#include "ClientCommunication/datamessage.h"
#include "../server/ServerCommunication/messageroutingtypes.h"
#include "../server/UserManagement/user.h"
#include <QVector>
#include "../server/Storage/idtypes.h"

int main(int argc, char *argv[])
{
    // qRegisterMetaType<OBJ_ID_TYPE>("OBJ_ID_TYPE");

    QApplication a(argc, argv);

    ViewControl* vc = new ViewControl();
    if( !vc->initialize() ) {
        return -1;
    }

    return a.exec();
}
