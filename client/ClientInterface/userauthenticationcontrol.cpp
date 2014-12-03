#include "userauthenticationcontrol.h"

UserAuthenticationControl::UserAuthenticationControl(QObject *parent) :
    QObject(parent)
{
}

bool UserAuthenticationControl::authenticateUser(quint16 id, User **user)
{
    // TODO: Implement Authentication
    *user = new User("TEST USER",User::STUDENT,0);

    return true;
}
