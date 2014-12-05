#ifndef SUCCESSMESSAGE_H
#define SUCCESSMESSAGE_H

/*
* successmessage.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* Message class:
* - Message containing an optional information string
*     and an optional confirmation number
*     (useful for returning an Order ID, for example)
* - Indicates a successful operation
*
* Traceability: CT-044
*
* Acknowledgements: None
*/

#include "message.h"
#include "../../server/Storage/idtypes.h"

class SuccessMessage : public Message
{
    Q_OBJECT
    Q_PROPERTY(QString info READ getInfoString WRITE setInfoString)
    Q_PROPERTY(OBJ_ID_TYPE reference READ getReference_unchecked WRITE setReference)
    Q_PROPERTY(OBJ_ID_TYPE referenceValidity READ getReferenceValidity WRITE setReferenceValidity)

public:
    /* Constructor
     *   To be used to create a container for deserialized data.
     * Side Effects: None
     */
    SuccessMessage();

    /* Constructor
     * in: Destination subsystem
     * in: Verb of the message
     * in: User associated with the message
     *      Can be null for messages that are to be sent to the
     *      client processes.
     *      Treated as a shared pointer.
     * in: Description of the result
     * in: Reference number
     * in: Whether there is a valid reference number
     * Side Effects: None
     */
    SuccessMessage(DEST_TYPE, ACTION_TYPE, User*, const QString& info = "",
                 const OBJ_ID_TYPE& reference = 0, bool hasReference = false);

    QString getInfoString() const { return info; }
    void setInfoString(const QString& s) { info = s; }

    /* Member Function: getReference_unchecked
     *   Serialization helper function only.
     * Returns this object's reference number, even if it isn't valid
     */
    OBJ_ID_TYPE getReference_unchecked(void) const { return reference; }
    void setReference(const OBJ_ID_TYPE& r) { reference = r; }

    /* Member Function: getReference
     * out: Reference number
     * Return Value: Whether or not the reference number is valid
     *   (If false, the output parameter is not modified.)
     */
     bool getReference(OBJ_ID_TYPE& reference) const;

     bool getReferenceValidity() const { return referenceValidity; }
     void setReferenceValidity(const bool& b) { referenceValidity = b; }

    /* Member Function: insertToDataStream
     *   Serialization function, which inserts the appropriate type constant
     *     into the data stream before the object's contents
     * inout: Data output stream
     * Side Effects: None
     * Return Value: None
     */
    virtual void insertToDataStream(QDataStream& ds) const;

private:
    QString info;
    OBJ_ID_TYPE reference;
    // Indicates whether this object stores a valid reference number
    bool referenceValidity;
};

#endif // SUCCESSMESSAGE_H
