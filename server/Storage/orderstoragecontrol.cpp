#include "orderstoragecontrol.h"

QSharedPointer<OrderStorageControl> OrderStorageControl::orderStorage(new OrderStorageControl());

bool OrderStorageControl::isInitialized = false;
bool OrderStorageControl::initializationAttempted = false;

bool OrderStorageControl::getOrderStorageControl(QSharedPointer<OrderStorageControl>& ptr) {
    if( !initializationAttempted ) {
        initializationAttempted = true;
        isInitialized = orderStorage->initialize();
    }
    if( isInitialized ) {
        ptr = orderStorage;
    }
    return isInitialized;
}


OrderStorageControl::OrderStorageControl(void)
{}

bool OrderStorageControl::initialize(void) {
    return MainStorageControl::getMainStorageControl(mainStorage);
}

bool OrderStorageControl::allPurchasingDetailsValid(
        QVector<PurchasingDetails*>*& purchasingDetails, QString& errorMsg) {

    if(purchasingDetails == 0){
        errorMsg = "Purchasing Details list is null.";
        return false;
    }

    QVectorIterator<PurchasingDetails*> i(*purchasingDetails);

    while (i.hasNext()) {
        QString query = "Select * from purchasingDetails where purchaseid=" + QString::number(i.peekNext()->getID());
        QSqlQuery result = mainStorage->runQuery(query);


        // lastError() is a string with a length of one (I think it might be a space?)
        // Strangest thing: QString.empty() returns false. Thus why the >1 check.
        if(result.lastError().text().length() > 1){
            errorMsg = result.lastError().text();
            return false;
        }
        if(!result.first()){
            // If there are no results and there were no errors, then the purchasing details are invalid.
            errorMsg = "Invalid Purchasing Details. Purchase ID:" + QString::number(i.peekNext()->getID()) + " does not exist.";
            return false;
        }

        PurchasingDetails* testDetails = new PurchasingDetails();
        if(result.first()){
            quint64 pid = result.value("purchaseid").toInt();
            testDetails->setID(pid);
            quint16 price = result.value("price").toFloat();
            testDetails->setPrice(price);
            QString vendor = result.value("vendor").toString();
            testDetails->setVendor(vendor);
            quint64 contentid = result.value("contentid").toInt();
            testDetails->setContentID(contentid);
            if(testDetails->getContentID() == i.peekNext()->getContentID() && testDetails->getPrice() == i.peekNext()->getPrice() && testDetails->getVendor()==i.peekNext()->getVendor())
            {

                delete testDetails;
                i.next();

            }
            else {
                errorMsg = "Invalid Purchasing Details. PurchaseID: " + QString::number(i.peekNext()->getID()) + " does not match details in database.";
                delete testDetails;
                return false;
            }
        }
    }

    return true;
}
