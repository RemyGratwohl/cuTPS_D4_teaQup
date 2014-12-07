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

    // Do any PD have said purchaseID?
    // If true, do all fields match exactly?
    // If still true, then PD is valid
    foreach(PurchasingDetails* details, *purchasingDetails){
        QString query = "Select * from purchasingDetails where purchaseid=" + QString::number(details->getID());
        QSqlQuery result = mainStorage->runQuery(query);
    }

    return false;
}
