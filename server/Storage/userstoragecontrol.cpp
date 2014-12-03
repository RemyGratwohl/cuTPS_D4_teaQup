#include "userstoragecontrol.h"

using namespace std;

UserStorageControl::UserStorageControl(QObject* parent)
    : QObject(parent)
{
}

bool UserStorageControl::getUser(int userid, User& user, string& errorMsg) {

    bool success = storage->getUser(userid, user, errorMsg);
    return false;
}
