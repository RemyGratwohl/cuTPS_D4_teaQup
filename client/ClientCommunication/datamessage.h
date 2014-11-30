#ifndef DATAMESSAGE_H
#define DATAMESSAGE_H

/*
* datamessage.h
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
* - Message containing data to be processed
*
* Traceability: CT-042
*
* Acknowledgements: None
*/

#include "message.h"

class DataMessage : public Message
{
    Q_OBJECT
public:
    /* Constructor
     * in: Destination subsystem
     * in: Verb of the message
     * in: User associated with the message
     *      Can be null for messages that are to be sent to the
     *      client processes.
     *      Treated as a shared pointer.
     * in: Contents of the data message
     * Side Effects: None
     */
    explicit DataMessage(DEST_TYPE, ACTION_TYPE, User*, QVector<SerializableQObject *>);

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

    QVector<SerializableQObject*> getData() const { return data; }

private:
    QVector<SerializableQObject*> data;
};

#endif // DATAMESSAGE_H
