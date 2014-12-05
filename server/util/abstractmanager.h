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
#include "../ServerCommunication/messageroutingtypes.h"

class AbstractManager : public QObject
{
    Q_OBJECT
protected:
    /* Constructor
     * in: Dispatcher to use for sending messages to the client
     *       (Also the parent of this object.)
     * in: The destination type constant indicating which
     *       subsystem on the client will be communicated with
     *       (i.e. the counterpart of this server-side subsystem).
     * Side Effects: None
     */
    AbstractManager(ServerDispatcher *dispatcher, DEST_TYPE);

public:
    /* Member Function: processMsg
     *   Handles a message received from the dispatcher,
     *     possibly resulting in messages sent back through the dispatcher
     * in: Message to be processed
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    virtual bool processMsg(const Message* msg) = 0;

    // Message processing helper functions
protected:
    /* Member Function: sendError
     *   Constructs an ErrorMessage object and sends it to the client.
     * in: Destination subsystem
     * in: Verb of the message
     * in: User associated with the message
     *      Can be null.
     *      Treated as a shared pointer.
     * in: Content of the error message
     * Side Effects: None
     * Return Value: Returns the result of ServerDispatcher::deliverMsg()
     */
    bool sendError(DEST_TYPE, ACTION_TYPE, User*, const QString& error);

    /* Member Function: sendData
     *   Constructs a DataMessage object and sends it to the corresponding
     *   subsystem on the client.
     * in: Verb of the message
     * in: User associated with the message
     *      Can be null for messages that are to be sent to the
     *      client processes.
     *      Treated as a shared pointer.
     * in: Contents of the data message, treated as an owned pointer
     * Side Effects: None
     * Return Value: Returns the result of ServerDispatcher::deliverMsg()
     */
    bool sendData(ACTION_TYPE, User*, QVector<SerializableQObject *>*);

    /* Member Function: sendSuccess
     *   Constructs a SuccessMessage object and sends it to the corresponding
     *   subsystem on the client.
     * in: Verb of the message
     * in: User associated with the message
     *      Can be null for messages that are to be sent to the
     *      client processes.
     *      Treated as a shared pointer.
     * in: Description of the result
     * in: Reference number
     * in: Whether there is a valid reference number
     * Side Effects: None
     * Return Value: Returns the result of ServerDispatcher::deliverMsg()
     */
    bool sendSuccess(ACTION_TYPE, User*, const QString& info = "",
                 const OBJ_ID_TYPE& reference = 0, bool hasReference = false);

signals:

public slots:

private:
    ServerDispatcher *dispatcher;

protected:
    DEST_TYPE ownDest;
};

#endif // ABSTRACTMANAGER_H
