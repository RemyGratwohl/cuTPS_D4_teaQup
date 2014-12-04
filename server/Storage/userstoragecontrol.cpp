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



/*
 * TODO Also put user querying functionality in the UserStorageControl class.
 */
bool UserStorageControl::getUser(int userid, User& user, string& errorMsg) {


    return false;
}
