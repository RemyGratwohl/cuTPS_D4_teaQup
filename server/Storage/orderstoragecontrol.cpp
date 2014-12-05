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
    return false;
}
