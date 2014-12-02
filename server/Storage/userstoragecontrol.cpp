#include "userstoragecontrol.h"

using namespace std;

UserStorageControl::UserStorageControl(QObject* parent)
    : QObject(parent)
{
    storage = new MainStorageControl(this);
}

bool UserStorageControl::getUser(int userid, User user, string errorMsg) {


    //return storage->getUser(userid, user, errorMsg);
}
