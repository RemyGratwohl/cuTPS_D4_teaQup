#ifndef SHOPPINGCARTCONTROL_H
#define SHOPPINGCARTCONTROL_H

/*
* shoppingcartcontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* ShoppingCartControl class:
* - Manages the shopping subsystem
*
* Traceability: CT-016
*
* Acknowledgements: None
*/

#include <QObject>
#include "shoppingcartview.h"
#include "../util/abstractviewcontroller.h"

#include "shoppingcart.h"
#include "billinginfoview.h"
#include "../../server/Purchasing/order.h"

class ShoppingCartControl : public AbstractViewController
{
    Q_OBJECT
public:
    /* Constructor
     *   Proxy of the AbstractViewController constructor.
     */
    ShoppingCartControl(ViewControl *viewControl, ClientDispatcher *dispatcher);

    /* Member Function: processMsg
     * Handles a message received from the dispatcher.
     * in: Message to be processed
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
   virtual bool processMsg(Message *msg);

    // Functions that will be called upon reception of non-error information from the server
    // -------------------------------------------------------------------------------------
    /* All input arguments will be deallocated by these functions
     */
protected:
    /* Member Function: receiveOrderConfirmation
     *   Processes a successful order (specifically, the confirmation message)
     * in: A confirmation message
     * in: The receipt number of the order (also present in the confirmation message string)
     * Side Effects: None
     * Return Value: True, if the operation succeeded
     */
    bool receiveOrderConfirmation(QString message, OBJ_ID_TYPE referenceNumber);

    /* Note: The dispatcher will not pass error messages to subsystems,
     * but will instead display them using the generic ViewControl::displayErrorString()
     * function.
     * This will be used to process unsuccessful order notifications.
     */

    // Functions to be called to send requests to the server
    // -----------------------------------------------------
    /* All input arguments will be deallocated by these functions
     */
public:
    /* Member Function: sendOrder
     *   Sends an order to the server for validation and processing.
     * in: Order to be processed
     * Side Effects: None
     * Return Value: None
     */
    void processOrder(Order* order);

    void handleShoppingList(QVector<ContentItem *>* list);

signals:

public slots:

private:
    BillingInfoView  *billingInfoView;
    ShoppingCart     *shoppingCart;
};

#endif // SHOPPINGCARTCONTROL_H
