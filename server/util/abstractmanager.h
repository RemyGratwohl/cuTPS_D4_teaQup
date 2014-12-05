#ifndef ABSTRACTMANAGER_H
#define ABSTRACTMANAGER_H

/*
* abstractmanager.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* AbstractManager class:
* - A helper class containing functionality common
*   to all server-side management subsystem control objects
*
* Traceability: CT-045
*
* Acknowledgements: None
*/

#include <QObject>
#include "../ServerCommunication/serverdispatcher.h"
#include "../client/ClientCommunication/message.h"

class AbstractManager : public QObject
{
    Q_OBJECT
protected:
    /* Constructor
     * in: Dispatcher to use for sending messages to the client
     *       (Also the parent of this object.)
     * Side Effects: None
     */
    AbstractManager(ServerDispatcher *dispatcher);

public:
    /* Member Function: processMsg
     *   Handles a message received from the dispatcher,
     *     possibly resulting in messages sent back through the dispatcher
     * in: Message to be processed
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    virtual bool processMsg(const Message* msg) = 0;

signals:

public slots:

private:
    ServerDispatcher *dispatcher;
};

#endif // ABSTRACTMANAGER_H
