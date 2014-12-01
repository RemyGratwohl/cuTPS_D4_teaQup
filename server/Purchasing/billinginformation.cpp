#include "billinginformation.h"
#include <QtDebug>

BillingInformation::BillingInformation() :
    name(),
    address(),
    institution()
{}

BillingInformation::BillingInformation(const QString& n,
                                       const QString& a,
                                       const QString& ins) :
    name(n),
    address(a),
    institution(ins)
{}

void BillingInformation::insertToDataStream(QDataStream& ds) const {
    SerializableQObject::insertToDataStream(ds, BILLINGINFO);
}

void BillingInformation::extractFromDataStream(QDataStream& ds) {
    quint32 serialType;
    ds >> serialType;
    if( serialType != BILLINGINFO ) {
        qDebug() << "BillingInformation::extractFromDataStream : Type constant of " << serialType
                 << " is not BILLINGINFO.";
    } else {
        SerializableQObject::extractFromDataStream(ds);
    }
}
