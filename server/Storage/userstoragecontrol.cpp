#include "userstoragecontrol.h"

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

bool UserStorageControl::getUser(int userid, User& user, string& errorMsg) {

    bool success = mainStorage->getUser(userid, user, errorMsg);
    return false;
}
