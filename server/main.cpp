#include <QCoreApplication>
#include "Storage/contentstoragecontrol.h"
#include "Storage/userstoragecontrol.h"
#include "ContentManagement/book.h"
#include "ServerCommunication/serverdispatcher.h"
#include "ServerCommunication/messageroutingtypes.h"
#include "../client/ClientCommunication/message.h"
#include "../client/ClientCommunication/errormessage.h"
#include <QDebug>

void bookTest();
void userTest();

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

void bookTest() {
   QSharedPointer<ContentStorageControl> contentAccess;
   contentAccess->getContentStorageControl(contentAccess);
   qDebug() << "ContentAccess Initialized";
   Book * testbook = new Book(-1, "The Host", 1, new PurchasingDetails(-1, 12.99, "Nano", -1), "", "Stephanie Meyer", "978-0316068048",
                              "http://www.stepheniemeyer.com/thehost.html", 2008,
                              "Little Brown and Company", "", "");
   Term * testTerm = new Term(-1, "W", 2014);
   Course * testCourse = new Course(-1, "CHEM1004: Generic Chemistry", 1);

   QString error = "";

   bool Success = contentAccess->addBook(testbook, testCourse, testTerm, error);

   if(!Success){
       qDebug() << "Add Book failed";
       qDebug() << "Error message: " + error;
   }

   else {
      qDebug() << "Success";
   }
}

void userTest() {
    QSharedPointer<UserStorageControl> userAccess;
    userAccess->getUserStorageControl(userAccess);


    OBJ_ID_TYPE userid = 100945234;
    User* user = new User(userid);
    QString error = "";

    bool Success = userAccess->getUser(userid, user, error);

    if(!Success){
        qDebug() << "Get User failed";
        qDebug() << "Error message: " + error;
    }
    else {
        qDebug() << "User's name: " + user->getName();
    }
}
