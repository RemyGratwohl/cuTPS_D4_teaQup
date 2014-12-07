#ifndef ABSTRACTVIEWCONTROLLER_H
#define ABSTRACTVIEWCONTROLLER_H

/*
* abstractviewcontroller.h
* ------------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* AbstractViewController class:
* - A helper class containing functionality common
*   to all client-side view subsystem control objects
*
* Traceability: CT-046
*
* Acknowledgements: None
*/

#include <QObject>

#include "../ClientCommunication/message.h"
#include "../../server/ServerCommunication/messageroutingtypes.h"
#include "../ClientCommunication/clientdispatcher.h"
#include "../ClientInterface/viewcontrol.h"

class AbstractViewController : public QObject
{
    Q_OBJECT
protected:
    /* Constructor
     * in: Parent of this object, also responsible for
     *       high-level view management
     * in: Dispatcher to use for sending messages to the server
     * in: The destination type constant indicating which
     *       subsystem on the server will be communicated with
     *       (i.e. the counterpart of this client-side subsystem).
     * Side Effects: None
     */
    AbstractViewController(ViewControl *viewControl, ClientDispatcher *dispatcher, DEST_TYPE);

public:
    /* Member Function: processMsg
     *   Handles a message received from the dispatcher.
     * in: Message to be processed
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    virtual bool processMsg(Message* msg) = 0;

    /* Member Function: getView
     *   Returns the view this controller is controlling.
     * in: None
     * Side Effects: None
     * Return Value: The QWidget for the view object.
     */
    QWidget* getView();

    /* Member Function: closeView
     *   Has the main view control remove the view from mainWindow
     * in: None
     * Side Effects: None
     * Return Value: None
     */
    void closeView();

    // Message processing helper functions
protected:

    /* Member Function: sendData
     *   Constructs a DataMessage object and sends it to the corresponding
     *   subsystem on the server.
     *   Cannot be used prior to user authentication, as it takes
     *   the current user from ViewControl.
     * in: Verb of the message
     * in: Contents of the data message, treated as an owned pointer
     * Side Effects: None
     * Return Value: Returns the result of ClientDispatcher::deliverMsg()
     */
    void sendData(ACTION_TYPE, QVector<SerializableQObject *>*);

signals:

public slots:

protected:
    ViewControl* viewControl;
    ClientDispatcher *dispatcher;
    DEST_TYPE ownDest;
    QWidget   *view;
};

#endif // ABSTRACTVIEWCONTROLLER_H
