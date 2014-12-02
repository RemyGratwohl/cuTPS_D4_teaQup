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
#include <QVector>

class DataMessage : public Message
{
    Q_OBJECT
public:
    /* Constructor
     *   To be used to create a container for deserialized data.
     * Side Effects: None
     */
    DataMessage();

    /* Constructor
     * in: Destination subsystem
     * in: Verb of the message
     * in: User associated with the message
     *      Can be null for messages that are to be sent to the
     *      client processes.
     *      Treated as a shared pointer.
     * in: Contents of the data message, treated as an owned pointer
     * Side Effects: None
     */
    DataMessage(DEST_TYPE, ACTION_TYPE, User*, QVector<SerializableQObject *>*);

    virtual ~DataMessage(void);

    /* Member Function: insertToDataStream
     *   Serialization function, which inserts the appropriate type constant
     *     into the data stream before the object's contents
     * inout: Data output stream
     * Side Effects: None
     * Return Value: None
     */
    virtual void insertToDataStream(QDataStream& ds) const;

    QVector<SerializableQObject*>* getData() const { return data; }

    /* Member Function: setFirstData
     *   To be used by SerializableObjectFactory
     * in: Data items being transferred
     * Side Effects: This object becomes the owner of 'data'
     * Return Value: True, if this object's data vector has been set.
     *   Returns false and does nothing if this object
     *     already has a vector of data.
     */
    bool setFirstData(QVector<SerializableQObject*>* data);

private:
    QVector<SerializableQObject*>* data;
};

#endif // DATAMESSAGE_H
