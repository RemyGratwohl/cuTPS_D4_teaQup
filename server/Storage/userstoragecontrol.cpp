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

bool UserStorageControl::getUser(OBJ_ID_TYPE& userid, User*& user, QString& errorMsg) {
    QString id = QString::number(userid);
    qDebug() << "GetUser() called with userid: " + id;

    QString query = "Select name, usertype from users where userid=" + id;
    QSqlQuery result = mainStorage->runQuery(query);

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
    else if (result.next()){
        errorMsg = "More than one user returned. Database is corrupted.";
        return false;
    }
    else {
        errorMsg = "User does not exist";
        return false;
    }

    return true;
}
