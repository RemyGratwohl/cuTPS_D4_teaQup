#include "shoppingcartcontrol.h"
#include <QDebug>

ShoppingCartControl::ShoppingCartControl(ViewControl *viewController, QObject *parent) :
    viewController(viewController),
    QObject(parent)
{
    shoppingCartView = new ShoppingCartView(this);
    billingInfoView  = new BillingInfoView(this);
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

QWidget* ShoppingCartControl::getView(){
    return shoppingCartView;
}

// TODO (Remy or Brandon) Stub implementation
bool receiveOrderConfirmation(QString message, OBJ_ID_TYPE referenceNumber) {
    return false;
}

// TODO (Bernard) Stub implementation
void processOrder(Order* order) {

}

