#ifndef ORDER_H
#define ORDER_H

/*
* order.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* Order class:
* - a Student user's order information
*
* Note:
*   Serialization and deserialization of the vector of ContentItems
*   stored in an order is handled by SerializableObjectFactory.
*
* Traceability: ET-008
*
* Acknowledgements: None
*/

#include "../ServerCommunication/serializableqobject.h"
#include "billinginformation.h"
#include "../ContentManagement/contentitem.h"
#include <QString>
#include <QVector>

class Order : public SerializableQObject
{
    Q_OBJECT
public:
    /* Constructor
     *   To be used to create a container for deserialized data.
     * Side Effects: None
     */
    Order(void);

    /* Constructor
     * in: Student user billing information
     * in: Content items to be ordered
     * Side Effects: The billing information object is adopted
     *   as a child of this object, but the vector
     *   of content items is treated as a shared pointer.
     */
    Order(BillingInformation *billingInfo,
          QVector<ContentItem*>* contentItems);

    virtual ~Order(void);

    /* Member Function: insertToDataStream
     *   Serialization function, which inserts the appropriate type constant
     *     into the data stream before the object's contents
     * inout: Data output stream
     * Side Effects: None
     * Return Value: None
     */
    virtual void insertToDataStream(QDataStream& ds) const;

    /* Member Function: extractFromDataStream
     *   Deserialization function
     * inout: Data input stream
     * Side Effects: None
     * Return Value: None
     */
    virtual void extractFromDataStream(QDataStream& ds);

    /* Member Function: setFirstContents
     *   To be used by SerializableObjectFactory
     * in: Content items being purchased
     * Side Effects: This object becomes the owner of 'content'
     * Return Value: True, if this object's contents have been set.
     *   Returns false and does nothing if this object
     *     already has a vector of content items.
     */
    bool setFirstContents(QVector<ContentItem*>* content);

private:
    BillingInformation *billingInfo;
    QVector<ContentItem*>* content;
    bool contentIsShared; // Flag indicating ownership of 'content'
};

#endif // ORDER_H
