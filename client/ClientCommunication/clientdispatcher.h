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
#include "ClientCommunication/message.h"

class ClientDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit ClientDispatcher(QObject *parent = 0);

    /* Member Function: deliverMsg
     *   Sends the message to the client process
     *   corresponding to the current connection.
     * in: The message object to send
     * Side Effects: 'msg' is deleted.
     * Return Value: Success indicator
     */
    bool deliverMsg(const Message*& msg) const;

signals:

public slots:

};

#endif // CLIENTDISPATCHER_H
