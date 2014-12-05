#ifndef ORDERCONTROL_H
#define ORDERCONTROL_H

/*
* ordercontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* OrderControl class:
* - handles the Student user's orders.
*
* Traceability: CT-015
*
* Acknowledgements: None
*/

#include "../util/abstractmanager.h"
#include "../Storage/orderstoragecontrol.h"
#include "order.h"

class OrderControl : public AbstractManager
{
    Q_OBJECT
public:
    /* Constructor
     * in: Dispatcher to use for sending messages to the client
     *       (Also the parent of this object.)
     * Side Effects: None
     * All input pointers are treated as shared pointers.
     */
    OrderControl(ServerDispatcher *dispatcher);

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
    /* Member Function: processOrder
     *   Validates and then sends an Order to the external payment system.
     *   Sends a success (confirmation) or error message back to the client.
     *
     * The first two parameters are used for passing messages
     * in: Action type of the return message
     * in: User associated with the current request
     *
     * in: Order to be processed
     *
     * Side Effects: None
     * Return Value: True, if the operation proceeded without
     *   internal errors (regardless of whether or not the order
     *   was valid or was sent successfully).
     */
    bool processOrder(ACTION_TYPE, User*, Order* order);

    // Helper functions used by processOrder()
private:
    /* Member Function: validateItems
     *   Validates the contents of an order
     * in: Order contents to be processed
     * out: Null, if one or more of the order contents are
     *        non-existent (e.g. recently deleted) or not for sale.
     *      Otherwise, outputs the purchasing details corresponding
     *        to the items being ordered. (These are aliases
     *        of the purchasing details in 'contentsIn'.)
     * out: QString to contain error messages, including warnings
     *        of invalid order contents
     * Side Effects: None
     * Return Value: True, if the operation proceeded without
     *   internal errors (regardless of whether or not the order
     *   was valid).
     */
    bool validateItems(const QVector<ContentItem*>* contentsIn,
                       QVector<PurchasingDetails*>*& validContents, QString& errorMsg);

    /* Member Function: sendToPaymentSystem
     *   Transfers the order to an external payment system
     *     so that the purchase can be made.
     *   Sends a message to the client containing
     *     the result of the communication. (In real life,
     *     this would trigger a redirection to the payment
     *     system's interface).
     *   For D4, it just returns an error message or a
     *     confirmation number.
     *
     * The first two parameters are used for passing messages
     * in: Action type of the return message
     * in: User associated with the current request
     *
     * in: Student user's billing information
     * in: Items to be purchased (owned by the caller)
     *
     * Side Effects: None
     * Return Value: True, if the operation proceeded without
     *   internal errors (regardless of whether or not the order
     *   was sent successfully - The connection with the payment
     *   system may be unreliable).
     */
    bool sendToPaymentSystem(ACTION_TYPE, User*,
                             const BillingInformation *billingInfo,
                             QVector<PurchasingDetails*>*& validContents);

private:
    QSharedPointer<OrderStorageControl> orderStorageControl;

    /* This data member is a placeholder for D4 as
     * an external payment system would return confirmation numbers
     * in a 'real life'.
     * This member is a counter used to demonstrate
     * basic tracking of purchases.
     * (For D4, purchases are not stored persistently, as there
     *  is no requirement for anyone to retrieve them later.)
     */
    quint64 referenceNumber;
};

#endif // ORDERCONTROL_H
