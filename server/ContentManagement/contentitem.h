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
    Q_PROPERTY(quint16 id READ getID WRITE setID)
    Q_PROPERTY(QString title READ getTitle WRITE setTitle)
    Q_PROPERTY(quint16 courseID READ getCourseID WRITE setCourseID)

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
            quint16 id,
            QString title,
            quint16 courseID,
            PurchasingDetails *purchaseDetails);

    virtual ~ContentItem(void);

    quint16 getID()   const { return identifier;   }
    void setID(quint16 id)   { identifier = id; }

    QString getTitle() const { return title; }
    void setTitle(const QString& t) { title = t; }

    quint16 getCourseID()   const { return courseID;   }
    void setCourseID(quint16 id)   { courseID = id; }

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
    /* Member Function: extractFromDataStream
     *   Deserialization function
     * inout: Data input stream
     * Side Effects: None
     * Return Value: None
     */
    virtual void extractFromDataStream(QDataStream& ds);

private:
    quint16 identifier;
    QString title;
    quint16 courseID;
    PurchasingDetails *purchaseDetails;
};

#endif // CONTENTITEM_H
