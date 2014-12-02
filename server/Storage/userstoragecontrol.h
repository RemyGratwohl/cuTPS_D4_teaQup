#ifndef USERSTORAGECONTROL_H
#define USERSTORAGECONTROL_H

/*
* userstoragecontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* UserStorageControl class:
* - handles the user aspect of the storage system
*
* Traceability: CT-038
*
* Acknowledgements: None
*/

#include <QObject>
#include "UserManagement/user.h"
#include "mainstoragecontrol.h"
#include <string>


class UserStorageControl : public QObject
{
    Q_OBJECT
public:
    /* Constructor
     *   Creates a fully-initialized UserStorageControl object
     * in: parent QObject
     * Side Effects: None
     */
    explicit UserStorageControl(QObject* parent = 0);

    /* Get User
     *  Retrieves the user from MainStorageControl
     * in: userid int
     * out: user User, errorMsg string
     * Side Effects: TBD
     */
    bool getUser(int userid, User& user, std::string& errorMsg);

    //bool processMsg(Message message);
    //bool addUser(User user);
    //bool updateUser(User user);
    //bool removeUser(User user);
    //bool getUserList(QVector<User> users);

private:

    MainStorageControl* storage;
};

#endif // USERSTORAGECONTROL_H
