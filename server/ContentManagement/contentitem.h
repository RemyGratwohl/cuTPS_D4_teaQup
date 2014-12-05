#ifndef CONTENTITEM_H
#define CONTENTITEM_H

/*
* contentitem.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* ContentItem class:
* - contains all data pertaining to the content items
* - can either be a Book, Chapter, or ChapterSection
* - contains purchasing details
*
* Traceability: ET-005
*
* Acknowledgements: None
*/

#include "../ServerCommunication/serializableqobject.h"
#include "purchasingdetails.h"
#include <QString>

class ContentItem : public SerializableQObject
{
    Q_OBJECT
    Q_PROPERTY(OBJ_ID_TYPE id READ getID WRITE setID)
    Q_PROPERTY(QString title READ getTitle WRITE setTitle)
    Q_PROPERTY(OBJ_ID_TYPE courseID READ getCourseID WRITE setCourseID)
    Q_PROPERTY(bool purchaseable READ isForSale WRITE setPurchaseability)
public:
    /* Constructor
     *   To be used to create a container for deserialized data.
     * Side Effects: None
     */
    ContentItem(void);

    /* Constructor
     * in: Content item ID
     * in: Title
     * in: Corresponding course ID
     * in: Purchasing details (null if not for sale)
     * Side Effects: Purchasing details is adopted
     *   as a child of this object.
     */
    ContentItem(
            OBJ_ID_TYPE id,
            QString title,
            OBJ_ID_TYPE courseID,
            PurchasingDetails *purchaseDetails);

    virtual ~ContentItem(void);

    OBJ_ID_TYPE getID()   const { return identifier;   }
    void setID(OBJ_ID_TYPE id)   { identifier = id; }

    QString getTitle() const { return title; }
    void setTitle(const QString& t) { title = t; }

    OBJ_ID_TYPE getCourseID()   const { return courseID;   }
    void setCourseID(OBJ_ID_TYPE& id)   { courseID = id; }

    bool isForSale() const { return purchaseable;   }
    void setPurchaseability(const bool& b)   { purchaseable = b; }

    /* Returns null if the content item is not for sale. */
    PurchasingDetails* getPurchasingDetails() const { return purchaseDetails; }

protected:
    /* Member Function: insertToDataStream
     *   Serialization function, which inserts the appropriate type constant
     *     into the data stream before the object's contents
     * inout: Data output stream
     * in: Type constant to use for deserialization.
     * Side Effects: None
     * Return Value: None
     */
    virtual void insertToDataStream(QDataStream& ds, SerializableType type) const;

public:
    /* Member Function: insertToDataStream
     *   Serialization function, which inserts the appropriate type constant
     *     into the data stream before the object's contents
     * inout: Data output stream
     * Side Effects: None
     * Return Value: None
     */
    virtual void insertToDataStream(QDataStream& ds) const = 0;

    /* Member Function: extractFromDataStream
     *   Deserialization function
     * inout: Data input stream
     * Side Effects: None
     * Return Value: None
     */
    virtual void extractFromDataStream(QDataStream& ds);

private:
    OBJ_ID_TYPE identifier;
    QString title;
    OBJ_ID_TYPE courseID;
    PurchasingDetails *purchaseDetails;
    /* Tracking whether or not purchaseDetails is null
     * is an unsatisfactory way of determining if the
     * ContentItem is for sale, because it would
     * require serializing the pointer's value
     * and testing the deserialized pointer value
     * to determine whether or not to allocate
     * PurchasingDetails.
     *
     * I felt that an explicit flag was more understandable.
     */
    bool purchaseable;
};

#endif // CONTENTITEM_H
