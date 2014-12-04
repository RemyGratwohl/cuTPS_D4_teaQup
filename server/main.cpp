#include <QCoreApplication>

#include "Storage/contentstoragecontrol.h"
#include "ContentManagement/book.h"
#include "ServerCommunication/serverdispatcher.h"
#include "ServerCommunication/messageroutingtypes.h"
#include "../client/ClientCommunication/message.h"
#include "../client/ClientCommunication/errormessage.h"
#include <QDebug>


int main(int argc, char *argv[])
{
    qRegisterMetaType<OBJ_ID_TYPE>("OBJ_ID_TYPE");

    //QCoreApplication a(argc, argv);

    // TEST -  ADD BOOK DB START
   QSharedPointer<ContentStorageControl> contentAccess;
   contentAccess->getContentStorageControl(contentAccess);
   qDebug() << "ContentAccess Initialized";
   Book * testbook = new Book(-1, "The Host", 1, NULL, "", "Stephanie Meyer", " 978-0316068048",
                              "http://www.stepheniemeyer.com/thehost.html", 2008,
                              "Little Brown and Company", "", "");

   QString error = "";
   qDebug() << "Before adding Book to storage";
   bool Success = contentAccess->addBook(testbook);
   if(!Success){
   qDebug() << "Add Book failed";
   qDebug() << "Error message: " + error;
   }
   else {
   qDebug() << "Success";
   }
   // TEST - ADD BOOK DB END

    /* testing start - feel free to comment this stuff out */

    ServerDispatcher* serverDispatcher = new ServerDispatcher(argc, argv);
    serverDispatcher->initialize();

    /* testing end */

    return serverDispatcher->exec();
}
