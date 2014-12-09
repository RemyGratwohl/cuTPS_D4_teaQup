#include <QCoreApplication>
#include "Storage/contentstoragecontrol.h"
#include "Storage/orderstoragecontrol.h"
#include "Storage/userstoragecontrol.h"
#include "ContentManagement/book.h"
#include "ServerCommunication/serverdispatcher.h"
#include "ServerCommunication/messageroutingtypes.h"
#include "../client/ClientCommunication/message.h"
#include "../client/ClientCommunication/errormessage.h"
#include <QDebug>


int main(int argc, char *argv[])
{
    // qRegisterMetaType<OBJ_ID_TYPE>("OBJ_ID_TYPE");
    /* testing start - feel free to comment this stuff out */

    ServerDispatcher* serverDispatcher = new ServerDispatcher(argc, argv);
    if( !serverDispatcher->initialize() ) {
        return -1;
    }

    /* testing end */

    return serverDispatcher->exec();
}

void getBooks(){
    QSharedPointer<ContentStorageControl> contentAccess;
    contentAccess->getContentStorageControl(contentAccess);
    QVector<Book*>* items = 0;
    QString error = "";
    bool Success = contentAccess->getBooks(items, error);
    if(Success){
        qDebug() << items->size();
    }
    else{
        qDebug() << "Fix your shit. " + error;
    }
}
