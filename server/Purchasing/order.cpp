#include "order.h"

Order::Order() :
    billingInfo(0),
    content(0),
    contentIsShared(true)
{
}

Order::Order(BillingInformation *billingInfo,
             QVector<ContentItem*>* contentItems) :
    billingInfo(billingInfo),
    content(contentItems),
    contentIsShared(true)
{
    if( billingInfo != 0 ) {
        billingInfo->setParent(this);
    }
}

Order::~Order(void) {
    if( !contentIsShared && content != 0 ) {
        QVectorIterator<ContentItem*> i(*content);
        while (i.hasNext()) {
            delete (i.next());
        }
        delete content;
        content = 0;
    }
}

void Order::insertToDataStream(QDataStream& ds) const {
    SerializableQObject::insertToDataStream(ds, ORDEROBJ);
    billingInfo->insertToDataStream(ds);
    QVectorIterator<ContentItem*> i(*content);
    while (i.hasNext()) {
        i.next()->insertToDataStream(ds);
    }
}

void Order::extractFromDataStream(QDataStream& ds) {
    SerializableQObject::extractFromDataStream(ds);
    billingInfo = new BillingInformation;
    billingInfo->extractFromDataStream(ds);
    billingInfo->setParent(this);
}

bool Order::setFirstContents(QVector<ContentItem*>* c) {
    if( content == 0 ) {
        contentIsShared = false;
        content = c;
        return true;
    }
    return false;
}
