#include "shoppingcartcontrol.h"
#include <QDebug>
#include "../ClientInterface/viewcontrol.h"

ShoppingCartControl::ShoppingCartControl(ViewControl *vc, ClientDispatcher *d) :
    AbstractViewController(vc, d, ORDERING)
{
    shoppingCartView = new ShoppingCartView(this);
    billingInfoView  = new BillingInfoView(this);
    shoppingCart     = new ShoppingCart(this);

    view = shoppingCartView; // Default view for the subystems
}

bool ShoppingCartControl::processMsg(Message *msg)
{
    bool result = true;
    DataMessage* dataMessage = qobject_cast<DataMessage*>(msg);
    ACTION_TYPE msgAction = dataMessage->getActionType();

    switch(msgAction)
    {
    case CREATE:
        qDebug() << "ShoppingCartControl: received CREATE message.";
        break;
    case RETRIEVE:
        qDebug() << "ShoppingCartControl: received RETRIEVE message.";
        break;
    case UPDATE:
        qDebug() << "ShoppingCartControl: received UPDATE message.";
        break;
    case DELETE:
        qDebug() << "ShoppingCartControl: received DELETE message.";
        break;
    default:
        qDebug() << "ShoppingCartControl: received incompatible message.";
        result = false;
        break;
    }

    delete dataMessage;
    dataMessage = 0;
    return result;
}

void ShoppingCartControl::changeActiveView(TYPE t)
{
    switch(t)
    {
    case(SHOPPINGCART):
        view = shoppingCartView;
        break;
    case(BILLINGINFO):
        view = billingInfoView;
        break;
    case(CONFIRMATION):
        break;
    default:
        break;
    }

    viewControl->changeView(ViewControl::SHOPPING_VIEW);
}

void ShoppingCartControl::handleShoppingList(QVector<ContentItem *>* list)
{
    shoppingCart->insertNewItems(list);
    ((ShoppingCartView *)view)->viewContentItems(shoppingCart->getShoppingList());
}

// TODO (Remy or Brandon) Stub implementation
bool receiveOrderConfirmation(QString message, OBJ_ID_TYPE referenceNumber) {
    return false;
}

// TODO (Bernard) Stub implementation
void processOrder(Order* order) {

}

