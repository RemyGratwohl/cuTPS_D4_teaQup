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
     *   Retrieves the user from MainStorageControl
     * in: OBJ_ID_TYPE userid used to identify the user
     * out: User to be altered
     *      (Passed in null, and remains null if the operation fails.)
     * out: QString to be altered in the event of an error
     * Side Effects: None
     * Return Value: True, if operation succeeded.
     * *******************************************
     * Note: -TBR (to be removed before 'release') If a user doesn't exist, it will return FALSE.
     * I may add error numbers, so that you can check that if the function returns false
     * You can check the first character in the string and if its a certain number
     * then you can handle each error differently.
     */
    bool getUser(OBJ_ID_TYPE& userid, User*& user, QString& errorMsg);

private:
    QSharedPointer<MainStorageControl> mainStorage;

private:
    // Singleton instance
    static QSharedPointer<UserStorageControl> userStorage;
    static bool isInitialized;
    static bool initializationAttempted;
};

#endif // USERSTORAGECONTROL_H
