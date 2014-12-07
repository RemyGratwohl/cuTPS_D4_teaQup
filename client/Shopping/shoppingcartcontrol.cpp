#include "shoppingcartcontrol.h"
#include <QDebug>
#include "../ClientInterface/viewcontrol.h"
#include "ClientCommunication/successmessage.h"

ShoppingCartControl::ShoppingCartControl(ViewControl *vc, ClientDispatcher *d) :
    AbstractViewController(vc, d, ORDERING)
{
    view = new ShoppingCartView(this);
    billingInfoView  = new BillingInfoView(this);
    shoppingCart     = new ShoppingCart(this);
}

bool ShoppingCartControl::processMsg(Message *msg)
{
    ACTION_TYPE msgAction = msg->getActionType();
    DEST_TYPE msgDest = msg->getDestType();

    if(msgDest != ownDest) {
        qDebug() << "ShoppingCartControl: Error - received a message for another subsystem.";
        return false;
    }

    // Validate action type
    if( msgAction != CREATE ) {
        qDebug() << "ShoppingCartControl: Error - received a message with an action type other than CREATE.";
        return false;
    }

    // Process success messages
    // ------------------------
    bool result = false;
    const SuccessMessage* successMessage = qobject_cast<const SuccessMessage*>(msg);
    if(successMessage != 0) {
        qDebug() << "ShoppingCartControl: Received success message.";

        // Ensure reference number is valid
        OBJ_ID_TYPE reference = static_cast<OBJ_ID_TYPE>(0);
        if( successMessage->getReference(reference) ) {
            result = receiveOrderConfirmation(successMessage->getInfoString(), reference);
        } else {
            qDebug() << "ShoppingCartControl: Error - Expected SuccessMessage to have a valid reference number.";
            result = false;
        }
    } else {
        qDebug() << "ShoppingCartControl: Error - Expected a message of type SuccessMessage.";
        result = false;
    }

    return result;
}

void ShoppingCartControl::handleShoppingList(QVector<ContentItem *>* list)
{
    shoppingCart->insertNewItems(list);
    ((ShoppingCartView *)view)->viewContentItems(shoppingCart->getShoppingList());
}

// TODO (Remy or Brandon) Stub implementation
bool ShoppingCartControl::receiveOrderConfirmation(QString message, OBJ_ID_TYPE referenceNumber) {
    return false;
}

void ShoppingCartControl::processOrder(Order* order) {
    QVector<SerializableQObject*>* data = new QVector<SerializableQObject*>();
    data->append(order);
    sendData(CREATE, data);
}

