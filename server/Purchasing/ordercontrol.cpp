#include "ordercontrol.h"
#include <QTextStream>
#include "../../client/ClientCommunication/datamessage.h"

OrderControl::OrderControl(ServerDispatcher *d)
    : AbstractManager(d, ORDERING), orderStorageControl(0), referenceNumber(0)
{}

bool OrderControl::initialize(void) {
    return OrderStorageControl::getOrderStorageControl(orderStorageControl);
}

bool OrderControl::processMsg(const Message *msg)
{
    QString error;
    ACTION_TYPE msgAction = INVALIDACTION;
    DEST_TYPE msgDest = INVALIDDEST;
    User* user = msg->getUser();

    // Input validation concerning the message dispatching
    // ---------------------------------------------------
    const DataMessage* dataMessage = qobject_cast<const DataMessage*>(msg);
    if(dataMessage == 0) {
        error = "OrderControl: Error - received a message which is not of type DataMessage.";
        return sendError(msgDest, msgAction, user, error);
    }

    msgAction = dataMessage->getActionType();
    msgDest = dataMessage->getDestType();

    if(msgDest != ownDest) {
        error = "OrderControl: Error - received a message for another subsystem.";
        return sendError(msgDest, msgAction, user, error);
    }

    // Input validation concerning the user
    // ------------------------------------
    if( !user->isOfType(User::STUDENT) ) {
        error =  "OrderControl: Error - Non-Student users cannot order content.";
        return sendError(msgDest, msgAction, user, error);
    }

    // Input validation concerning the content of the message
    // ------------------------------------------------------
    QVector<SerializableQObject*>* data = dataMessage->getData();
    if( data->size() != 1 ) {
        error =  "OrderControl: Error - Message data vector has a length other than 1."
                 " Presently, all messages are expected to contain one element.";
        return sendError(msgDest, msgAction, user, error);
    }
    Order* order = qobject_cast<Order*>(data->first());
    if( order == 0 ) {
        error =  "OrderControl: Error - Message data vector has a null first element, "
                "or a first element which is not an Order.";
        return sendError(msgDest, msgAction, user, error);
    }

    // Determine which operation to complete and perform it
    // ----------------------------------------------------
    bool result = true;

    switch(msgAction)
    {

    case CREATE:
        qDebug() << "OrderControl: received CREATE message.";
        result = processOrder(msgAction, user, order);
        break;

    default:
        error =  "OrderControl: Unexpected message action type.";
        return sendError(msgDest, msgAction, user, error);
    }

    return result;
}

bool OrderControl::processOrder(ACTION_TYPE type, User* user, Order* order) {
    bool result = true;
    const QVector<ContentItem*>* contentsIn = order->getContents();
    QVector<PurchasingDetails*>* validContents = 0;
    QString error;
    result = validateItems(contentsIn, validContents, error);
    if( !result || validContents == 0 ) {
        // Critical error or invalid order
        sendError(ownDest, type, user, error);
        if( validContents != 0 ) {
            delete validContents;
            validContents = 0;
        }
        return result;
    }

    const BillingInformation *billingInfo = order->getBillingInformation();
    result = sendToPaymentSystem(type, user, billingInfo, validContents);
    delete validContents;
    validContents = 0;
    return result;
}

bool OrderControl::validateItems(const QVector<ContentItem*>* contentsIn,
                   QVector<PurchasingDetails*>*& validContents, QString& errorMsg) {
    QVector<PurchasingDetails*>* pds = new QVector<PurchasingDetails*>();
    QVectorIterator<ContentItem*> i(*contentsIn);
    PurchasingDetails* pd = 0;
    while (i.hasNext()) {
        pd = i.next()->getPurchasingDetails();
        if( pd == 0 ) {
            delete pds;
            errorMsg = "At least one item is not for sale.";
            return true;
        }
        pds->append(pd);
    }
    if( !orderStorageControl->allPurchasingDetailsValid(pds, errorMsg) ) {
        errorMsg = "One or more items was not validated by searching the database.";
        delete pds;
    } else {
        validContents = pds;
    }
    return true;
}

bool OrderControl::sendToPaymentSystem(ACTION_TYPE type, User* user,
                                       const BillingInformation *billingInfo,
                                       QVector<PurchasingDetails*>*& validContents) {
    QString msg;
    QTextStream textStream(&msg, QIODevice::ReadWrite);
    textStream << "Order processed: #" << referenceNumber
                  << " since the last system startup.";
    textStream << " " << validContents->size() << " items ordered under the name \""
               << billingInfo->getName() << "\".";
    ++referenceNumber;
    return sendSuccess(type, user, msg, referenceNumber, true);
}
