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
* - This is a singleton class
*
* Traceability: CT-038
*
* Acknowledgements: None
*/

#include <QObject>
#include "UserManagement/user.h"
#include "mainstoragecontrol.h"
#include <QString>
#include <QSharedPointer>


class UserStorageControl : public QObject
{
    Q_OBJECT

public:
    /* Static Member Function: getUserStorageControl
     * out: Instance of UserStorageControl, or nothing, if
     *        the UserStorageControl instance failed to initialize.
     * Side Effects: None
     * Return Value: True, if the UserStorageControl object
     *   is properly initialized.
     */
    static bool getUserStorageControl(QSharedPointer<UserStorageControl>& ptr);

protected:
    /* Constructor
     *   Essentially does nothing
     * Side Effects: None
     */
    UserStorageControl(void);

    /* Member Function: initialize
     * Returns false if this object does not initialize properly.
     */
    bool initialize(void);

public:

    /* Get User
     *  Retrieves the user from MainStorageControl
     * in: userid int
     * out: user User, errorMsg string
     * Side Effects: TBD
     */
    bool getUser(OBJ_ID_TYPE& userid, User*& user, QString& errorMsg);

    //bool processMsg(Message message);
    //bool addUser(User user);
    //bool updateUser(User user);
    //bool removeUser(User user);
    //bool getUserList(QVector<User> users);

private:
    QSharedPointer<MainStorageControl> mainStorage;

private:
    // Singleton instance
    static QSharedPointer<UserStorageControl> userStorage;
    static bool isInitialized;
    static bool initializationAttempted;
};

#endif // USERSTORAGECONTROL_H
