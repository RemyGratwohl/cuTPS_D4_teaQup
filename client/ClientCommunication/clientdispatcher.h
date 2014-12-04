#ifndef CLIENTDISPATCHER_H
#define CLIENTDISPATCHER_H

/*
* clientdispatcher.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* ClientDispatcher class:
* - Responsbile for passing around Message objects to the other client-side subsystems.
*
* Traceability: CT-029
*
* Acknowledgements: None
*/

#include <QObject>
#include "ClientCommunication/networklink.h"
#include "ContentView/contentviewcontrol.h"
#include "CourseView/courseviewcontrol.h"
#include "Shopping/shoppingcartcontrol.h"
#include "ClientCommunication/message.h"
#include "ClientCommunication/errormessage.h"

class ClientDispatcher : public QObject
{
    Q_OBJECT
public:
    // owns control pointers that were created in another control object
    explicit ClientDispatcher(QObject *parent,
                              ContentViewControl* contentControl,
                              CourseViewControl* courseControl,
                              ShoppingCartControl* shoppingControl
                              );

    /* Member Function: directMsg
     *   Sends the message to the proper client subsystem
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
    bool initialize();

signals:

public slots:

private:
    NetworkLink*         networkLink;
    ContentViewControl*  contentViewControl;
    CourseViewControl*   courseViewControl;
    ShoppingCartControl* shoppingCartControl;
};

#endif // CLIENTDISPATCHER_H
