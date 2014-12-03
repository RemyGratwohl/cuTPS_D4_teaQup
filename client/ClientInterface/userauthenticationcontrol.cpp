#include "userauthenticationcontrol.h"

UserAuthenticationControl::UserAuthenticationControl(QObject *parent) :
    QObject(parent)
{
}

bool UserAuthenticationControl::authenticateUser(QString username, User **user)
{
    // TODO: Implement Authentication
    *user = new User(username,User::STUDENT,0);

    return true;
}
