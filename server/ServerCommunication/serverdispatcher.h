#ifndef SERVERDISPATCHER_H
#define SERVERDISPATCHER_H

/*
* serverdispatcher.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* ServerDispatcher class:
* - Initializes server control flow
* - Sends and receives network communication
*
* Traceability: CT-028
*
* Acknowledgements: None
*/

#include <QObject>
#include <QCoreApplication>
#include <QDebug>

#include "networklink.h"
#include "../ContentManagement/contentcontrol.h"
#include "../CourseManagement/coursecontrol.h"
#include "../Purchasing/ordercontrol.h"
#include "../UserManagement/usercontrol.h"
#include "../Storage/mainstoragecontrol.h"
#include "../../client/ClientCommunication/message.h"
#include "../../client/ClientCommunication/errormessage.h"

class ServerDispatcher : public QCoreApplication
{
    Q_OBJECT
public:

    /* Constructor
     * Parameters: Refer to the QCoreApplication constructor
     * Side Effects: None
     */
    explicit ServerDispatcher(int & argc, char ** argv);

    /* Member Function: directMsg
     *   Sends the message to the proper server subsystem
     * in: The message object to send
     * Side Effects: None
     * Return Value: Success indicator
     */
    bool directMsg(Message *msg) const;

    /* Member Function: deliverMsg
     *   Sends the message to the client process
     *   corresponding to the current connection.
     * in: The message object to send
     * Side Effects: 'msg' is deleted.
     * Return Value: Success indicator
     */
    bool deliverMsg(Message *&msg) const;

    /* Member Function: initialize()
     * The effective constructor, which returns
     * false if system startup is unsuccessful.
     */
    bool initialize(void);

signals:

public slots:

private:
    NetworkLink*        networkLink;
    ContentControl*     contentControl;
    CourseControl*      courseControl;
    OrderControl*       orderControl;
    UserControl*        userControl;
    MainStorageControl* storageControl;

};

#endif // SERVERDISPATCHER_H
