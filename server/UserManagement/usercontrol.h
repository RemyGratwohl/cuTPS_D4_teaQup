#ifndef USERCONTROL_H
#define USERCONTROL_H

/*
* usercontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* UserControl class:
* - handles user authentication
* - this class is a merge of UserControl and UserAuthenticationServerControl,
*   due to the limited amount of functionality needed for D4.
*
* Traceability: CT-032, CT-033
*
* Acknowledgements: None
*/

#include "../util/abstractmanager.h"
#include "../Storage/userstoragecontrol.h"

class UserControl : public AbstractManager
{
    Q_OBJECT
public:
    /* Constructor
     * in: Dispatcher to use for sending messages to the client
     *       (Also the parent of this object.)
     * Side Effects: None
     * All input pointers are treated as shared pointers.
     */
    UserControl(ServerDispatcher *dispatcher);

    /* Member Function: initialize
     * Returns false if this object does not initialize properly.
     */
    bool initialize(void);

    /* Member Function: processMsg
     *   Handles a message received from the dispatcher,
     *     possibly resulting in messages sent back through the dispatcher
     * in: Message to be processed
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    virtual bool processMsg(const Message* msg);

    // Helper functions used by processMsg()
private:
    /* Member Function: authenticateUser
     * in: User passed in with an ID only,
     * out: User output with all information (if found).
     *      (Passed in null, and remains null if the operation fails
     *       or if no user is found.)
     * out: QString to be altered in the event of an error to hold an error message
     * Side Effects: None
     * Return Value: True, if the user was found.
     */
    bool authenticateUser(const User* userIn, User*& userOut, QString& errorMsg);

private:
    QSharedPointer<UserStorageControl> userStorageControl;
};

#endif // USERCONTROL_H
