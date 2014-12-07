#include "viewcontrol.h"
#include <QMessageBox>
#include "../server/ServerCommunication/messageroutingtypes.h"
#include "../server/ContentManagement/book.h"
#include "../server/ContentManagement/chapter.h"

ViewControl::ViewControl(QObject *parent) :
    QObject(parent)
{
    loginWindow = new LoginWindow(this);
    mainWindow  = new MainWindow(this);

    clientDispatcher = new ClientDispatcher(this, this);
    clientDispatcher->initialize();

    loginWindow->show(); // Show the initial window (login)
}

bool ViewControl::begin()
{
    /* send test message to server
    QVector<SerializableQObject *>* data = new QVector<SerializableQObject *>();
    Message* newMessage = new DataMessage(CONTENT, UPDATE, new User(User::STUDENT), data);
    clientDispatcher->deliverMsg(newMessage);

    // display a list of content items in main window
    QVector<SerializableQObject *>* list = new QVector<SerializableQObject *>();

    Book* testBook = new Book(-1, "The Host", 1, new PurchasingDetails(), "", "Stephanie Meyer", " 978-0316068048",
                               "http://www.stepheniemeyer.com/thehost.html", 2008,
                               "Little Brown and Company", "", "");
    list->push_back(qobject_cast<SerializableQObject*>(testBook));

    testBook = new Book(-1, "The Hostee", 1, new PurchasingDetails(), "", "Stephanie Meyer", " 978-0316068048",
                               "http://www.stepheniemeyer.com/thehost.html", 2008,
                               "Little Brown and Company", "", "");
    list->push_back(qobject_cast<SerializableQObject*>(testBook));

    testBook = new Book(-1, "The Hoster", 1, new PurchasingDetails(), "", "Stephanie Meyer", " 978-0316068048",
                               "http://www.stepheniemeyer.com/thehost.html", 2008,
                               "Little Brown and Company", "", "");
    list->push_back(qobject_cast<SerializableQObject*>(testBook));

    testBook = new Book(-1, "The Hosterer", 1, new PurchasingDetails(), "", "Stephanie Meyer", " 978-0316068048",
                               "http://www.stepheniemeyer.com/thehost.html", 2008,
                               "Little Brown and Company", "", "");
    list->push_back(qobject_cast<SerializableQObject*>(testBook));

    Chapter* testChapter = new Chapter(-1, "The Hostererest", 1, new PurchasingDetails(), -1, 1, " 978-0316068048-1");
    list->push_back(qobject_cast<SerializableQObject*>(testChapter));

    studentView->viewContentItems(data);
    */
    return true;
}

void ViewControl::setShoppingList(QVector<SerializableQObject *>* list)
{
    shoppingController->handleShoppingList(list);
}

bool ViewControl::processMsg(Message *msg)
{
    DEST_TYPE msgDest = msg->getDestType();

    switch(msgDest)
    {
    case ORDERING:
        // orderControl handles message
        return shoppingController->processMsg(msg);
        break;
    case USER:
        // user auth
        break;
    case CONTENT:
        // contentControl handles message
        return contentController->processMsg(msg);
        break;
    case COURSE:
        // courseControl handles message
        return courseController->processMsg(msg);
        break;
    default:
        return false;
        break;
    }

    return false;
}

bool ViewControl::authenticateUser(OBJ_ID_TYPE id)
{
    if(authenticator->authenticateUser(id, &currentUser))
    {
        loginWindow->hide();
        mainWindow->show();

        if(currentUser->getType() == User::STUDENT)
        {
            studentView        = new StudentView(this);
            shoppingController = new ShoppingCartControl(this);
            mainWindow->addView(studentView);
        }else if(currentUser->getType() == User::CONTENTMGR)
        {
            contentController  = new ContentViewControl(this);
            courseController   = new CourseViewControl(this);
            changeView(CONTENT_VIEW);
        }else if (currentUser ->getType() == User::ADMIN)
        {
            qDebug() << "Not implemented";
        }else{
            qDebug() << "Invalid User Type Detected";
            return false;
        }

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
    case(SHOPPING_VIEW):
        mainWindow->setCentralWidget(shoppingController->getView());
        break;
    case(CONTENT_VIEW):
        mainWindow->setCentralWidget(contentController->getView());
        break;
    case(COURSE_VIEW):
        break;
    default:
        break;
    }

    return true;
}
