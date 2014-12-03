#include "purchasingdetails.h"
#include <QtDebug>

PurchasingDetails::PurchasingDetails() :
    identifier(0), price(0), vendor(), contentID(0)
{
}

PurchasingDetails::PurchasingDetails(
        OBJ_ID_TYPE id,
        OBJ_ID_TYPE p,
        QString v,
        OBJ_ID_TYPE cID) :
    identifier(id), price(p), vendor(v), contentID(cID) {}

void PurchasingDetails::insertToDataStream(QDataStream& ds) const {
    SerializableQObject::insertToDataStream(ds, PURCHASEDETAILS);
}

void PurchasingDetails::extractFromDataStream(QDataStream& ds) {
    quint32 serialType;
    ds >> serialType;
    if( serialType != PURCHASEDETAILS ) {
        qDebug() << "PurchasingDetails::extractFromDataStream : Type constant of " << serialType
                 << " is not PURCHASEDETAILS.";
    } else {
        SerializableQObject::extractFromDataStream(ds);
    }
}
