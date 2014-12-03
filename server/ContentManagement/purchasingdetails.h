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
#include "../Storage/idtypes.h"

class PurchasingDetails : public SerializableQObject
{
    Q_OBJECT
    Q_PROPERTY(OBJ_ID_TYPE price READ getPrice WRITE setPrice)
    Q_PROPERTY(QString vendor READ getVendor WRITE setVendor)
    Q_PROPERTY(OBJ_ID_TYPE contentID READ getContentID WRITE setContentID)
    Q_PROPERTY(OBJ_ID_TYPE id READ getID WRITE setID)

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
            OBJ_ID_TYPE id,
            OBJ_ID_TYPE price,
            QString vendor,
            OBJ_ID_TYPE contentID);

    OBJ_ID_TYPE getID()   const { return identifier;   }
    void setID(OBJ_ID_TYPE id)   { identifier = id; }

    OBJ_ID_TYPE getPrice()   const { return price;   }
    void setPrice(OBJ_ID_TYPE p)   { price = p; }

    QString getVendor() const { return vendor; }
    void setVendor(const QString& v) { vendor = v; }

    OBJ_ID_TYPE getContentID()   const { return contentID;   }
    void setContentID(OBJ_ID_TYPE id)   { contentID = id; }

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
    OBJ_ID_TYPE identifier;
    OBJ_ID_TYPE price; // Cents
    QString vendor;
    OBJ_ID_TYPE contentID;
};

#endif // PURCHASINGDETAILS_H
