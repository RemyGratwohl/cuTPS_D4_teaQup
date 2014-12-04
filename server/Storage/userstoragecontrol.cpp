#include "userstoragecontrol.h"
#include <QDebug>
#include <QSqlQuery>

using namespace std;

QSharedPointer<UserStorageControl> UserStorageControl::userStorage(new UserStorageControl());

bool UserStorageControl::isInitialized = false;
bool UserStorageControl::initializationAttempted = false;

bool UserStorageControl::getUserStorageControl(QSharedPointer<UserStorageControl>& ptr) {
    if( !initializationAttempted ) {
        initializationAttempted = true;
        isInitialized = userStorage->initialize();
    }
    if( isInitialized ) {
        ptr = userStorage;
    }
    return isInitialized;
}


UserStorageControl::UserStorageControl(void)
{}

bool UserStorageControl::initialize(void) {
    return MainStorageControl::getMainStorageControl(mainStorage);
}

// TBR - TODO: UPDATE DOC FOR THIS FUNCTION
bool UserStorageControl::getUser(OBJ_ID_TYPE& userid, User*& user, QString& errorMsg) {


    qDebug() << "GetUser() called with userid: " + QString::number(userid);

    // Build Query
    QString query = "Select name, usertype from users where userid=" + QString::number(userid);

    // Run query and get result set object
    QSqlQuery result = mainStorage->runQuery(query);

    // lastError() is a string with a length of one (I think it might be a space?)
    // Strangest thing: QString.empty() returns false. Thus why the >1 check.
    if(result.lastError().text().length() > 1){
        errorMsg = result.lastError().text();
        return false;
    }

    if(result.first()){
        QString name = result.value("name").toString();
        user->setName(name);
        quint16 type = result.value("usertype").toInt();
        user->setType(type);
    }
    // If there is more than one user returned, return false because something is wrong with the database
    else if (result.next()){
        errorMsg = "More than one user returned. Database is corrupted.";
        return false;
    }
    // If there are no results and there were no errors, then the user does not exist.
    else {
        errorMsg = "User does not exist";
        return false;
    }

    return true;
}
