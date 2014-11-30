#include "contentitem.h"

ContentItem::ContentItem() :
    identifier(0), title(), courseID(0), purchaseDetails(0)
{
}

ContentItem::ContentItem(quint16 id,
                         QString t,
                         quint16 cID,
                         PurchasingDetails *pd) :
    identifier(id), title(t), courseID(cID), purchaseDetails(pd)
{
    if( pd != 0 ) {
        pd->setParent(this);
    }
}

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
