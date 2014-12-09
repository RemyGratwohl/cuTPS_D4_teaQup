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

void addBookTest();
void userTest();
void validOrderTest();
void getBooks();

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

void validOrderTest() {
    QSharedPointer<OrderStorageControl> orderAccess;
    orderAccess->getOrderStorageControl(orderAccess);
    QString error = "";

    // Invalid list
    QVector<PurchasingDetails*>* orderList1 = new QVector<PurchasingDetails*>();
    PurchasingDetails* pDeets1 = new PurchasingDetails(1, 300.99, "TakinYourDeets", 2);
    PurchasingDetails* pDeets2 = new PurchasingDetails(3, 9.99, "TakinYourDeets", 2);
    orderList1->push_back(pDeets1);
    orderList1->push_back(pDeets2);

    bool Success1 = orderAccess->allPurchasingDetailsValid(orderList1, error);
    if(!Success1){
        if(error.length() > 1)
            qDebug() << "ERROR: " + error;
        qDebug() << "One or more of the Purchasing Details is invalid. This is supposed to happen.";
    }
    // Valid list
    QVector<PurchasingDetails*>* orderList2 = new QVector<PurchasingDetails*>();
    PurchasingDetails* pDeets3 = new PurchasingDetails(1, 300.99, "TakinYourDeets", 2);
    PurchasingDetails* pDeets4 = new PurchasingDetails(6, 9.99, "TakinYourDeets", 20);
    orderList2->push_back(pDeets3);
    orderList2->push_back(pDeets4);
    Success1 = orderAccess->allPurchasingDetailsValid(orderList2, error);
    if(Success1){
        qDebug() << "All details valid!";
    }
    else{
        qDebug() << "Something went wrong! " + error;
    }

    delete orderList1;
    delete orderList2;
    delete pDeets1;
    delete pDeets2;
    delete pDeets3;
    delete pDeets4;
}

void addBookTest() {
   QSharedPointer<ContentStorageControl> contentAccess;
   contentAccess->getContentStorageControl(contentAccess);

   Book * testbook = new Book(23, "The Host", 1, new PurchasingDetails(-1, 12.99, "Nano", -1), "", "Stephanie Meyer", "978-0316068048",
                              "http://www.stepheniemeyer.com/thehost.html", 2008,
                              "Little Brown and Company", "", "");
   Term * testTerm = new Term(1, "F", 2014);
   Course * testCourse = new Course(1, "CHEM1004: Generic Chemistry", 1);

   QString error = "";

   bool Success = contentAccess->addBook(testbook, testCourse, testTerm, error);

   if(!Success){
       qDebug() << "Add Book failed";
       qDebug() << "Error message: " + error;
   }

   else {
      qDebug() << "Success";
   }

   qDebug() << "Removing book";
   Success = contentAccess->removeBook(testbook, error);
   if(Success){
       qDebug() << "Book successfully removed!";
   }

   delete testbook;
   delete testTerm;
   delete testCourse;
}

void userTest() {
    QSharedPointer<UserStorageControl> userAccess;
    userAccess->getUserStorageControl(userAccess);


    OBJ_ID_TYPE userid = 100945234;
    User* user = 0;
    QString error = "";

    bool Success = userAccess->getUser(userid, user, error);

    if(!Success){
        qDebug() << "Get User failed";
        qDebug() << "Error message: " + error;
    }
    else {
        qDebug() << "User's name: " + user->getName();
        delete user;
    }

}
