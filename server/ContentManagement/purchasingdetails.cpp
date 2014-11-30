#include "purchasingdetails.h"
#include <QtDebug>

PurchasingDetails::PurchasingDetails() :
    identifier(0), price(0), vendor(), contentID(0)
{
}

PurchasingDetails::PurchasingDetails(
        quint16 id,
        quint16 p,
        QString v,
        quint16 cID) :
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
