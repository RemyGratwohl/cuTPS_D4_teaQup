#include "contentitem.h"

ContentItem::ContentItem() :
    identifier(0), title(), courseID(0), purchaseDetails(0)
{
}

ContentItem::ContentItem(OBJ_ID_TYPE id,
                         QString t,
                         OBJ_ID_TYPE cID,
                         PurchasingDetails *pd) :
    identifier(id), title(t), courseID(cID), purchaseDetails(pd)
{
    if( pd != 0 ) {
        pd->setParent(this);
    }
}

ContentItem::~ContentItem() {}

void ContentItem::insertToDataStream(QDataStream& ds, SerializableType type) const {
    SerializableQObject::insertToDataStream(ds, type);
    purchaseDetails->insertToDataStream(ds);
}

void ContentItem::extractFromDataStream(QDataStream& ds) {
    SerializableQObject::extractFromDataStream(ds);
    purchaseDetails = new PurchasingDetails;
    purchaseDetails->extractFromDataStream(ds);
    purchaseDetails->setParent(this);
}
