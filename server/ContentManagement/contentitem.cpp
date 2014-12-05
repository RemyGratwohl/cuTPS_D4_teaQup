#include "contentitem.h"

ContentItem::ContentItem() :
    identifier(0), title(), courseID(0), purchaseDetails(0),
    purchaseable(false)
{}

ContentItem::ContentItem(OBJ_ID_TYPE id,
                         QString t,
                         OBJ_ID_TYPE cID,
                         PurchasingDetails *pd) :
    identifier(id), title(t), courseID(cID), purchaseDetails(pd)
{
    purchaseable = (pd != 0);
    if( purchaseable ) {
        pd->setParent(this);
    }
}

ContentItem::~ContentItem() {}

void ContentItem::insertToDataStream(QDataStream& ds, SerializableType type) const {
    SerializableQObject::insertToDataStream(ds, type);
    if( purchaseable ) {
        purchaseDetails->insertToDataStream(ds);
    }
}

void ContentItem::extractFromDataStream(QDataStream& ds) {
    SerializableQObject::extractFromDataStream(ds);
    if( purchaseable ) {
        purchaseDetails = new PurchasingDetails;
        purchaseDetails->extractFromDataStream(ds);
        purchaseDetails->setParent(this);
    } else {
        purchaseDetails = 0;
    }
}
