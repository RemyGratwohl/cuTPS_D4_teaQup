#ifndef PURCHASINGDETAILS_H
#define PURCHASINGDETAILS_H

/*
* purchasingdetails.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* PurchasingDetails class:
* - contains all data pertaining to the purchasing details
*   of content items that are for sale
*
* Traceability: ET-011
*
* Acknowledgements: None
*/

#include "../ServerCommunication/serializableqobject.h"
#include <QString>

class PurchasingDetails : public SerializableQObject
{
    Q_OBJECT
    Q_PROPERTY(quint16 price READ getPrice WRITE setPrice)
    Q_PROPERTY(QString vendor READ getVendor WRITE setVendor)
    Q_PROPERTY(quint16 contentID READ getContentID WRITE setContentID)
    Q_PROPERTY(quint16 id READ getID WRITE setID)

public:
    /* Constructor
     *   To be used to create a container for deserialized data.
     * Side Effects: None
     */
    PurchasingDetails(void);

    /* Constructor
     * in: Purchasing details ID
     * in: Price (in cents - a natural number)
     * in: Vendor name
     * in: Corresponding content ID
     * Side Effects: None
     */
    PurchasingDetails(
            quint16 id,
            quint16 price,
            QString vendor,
            quint16 contentID);

    quint16 getID()   const { return identifier;   }
    void setID(quint16 id)   { identifier = id; }

    quint16 getPrice()   const { return price;   }
    void setPrice(quint16 p)   { price = p; }

    QString getVendor() const { return vendor; }
    void setVendor(const QString& v) { vendor = v; }

    quint16 getContentID()   const { return contentID;   }
    void setContentID(quint16 id)   { contentID = id; }

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

private:
    quint16 identifier;
    quint16 price; // Cents
    QString vendor;
    quint16 contentID;
};

#endif // PURCHASINGDETAILS_H
