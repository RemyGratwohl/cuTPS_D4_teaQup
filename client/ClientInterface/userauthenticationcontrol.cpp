#include "userauthenticationcontrol.h"

UserAuthenticationControl::UserAuthenticationControl(QObject *parent) :
    QObject(parent)
{
}

bool UserAuthenticationControl::authenticateUser(OBJ_ID_TYPE id, User*& user)
{
    // TODO: Implement Authentication
    user = new User("TEST USER",User::STUDENT,0);

    return true;
}
