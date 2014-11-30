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
#include "networklink.h"
#include "../../client/ClientCommunication/message.h"

class ServerDispatcher : public QCoreApplication
{
    Q_OBJECT
public:

    /* Constructor
     * Parameters: Refer to the QCoreApplication constructor
     * Side Effects: None
     */
    explicit ServerDispatcher(int & argc, char ** argv);

    /* Member Function: initialize()
     * The effective constructor, which returns
     * false if system startup is unsuccessful.
     */
    bool initialize(void);

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

private:
    // TODO subsystem control objects

    NetworkLink* networkLink;

};

#endif // SERVERDISPATCHER_H
