#ifndef MESSAGE_H
#define MESSAGE_H

/*
* message.h
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
* - Abstract class defining messages to be sent over the network.
*
* Traceability: CT-007
*
* Acknowledgements: None
*/

#include <QObject>
#include <QDataStream>
#include "../server/ServerCommunication/serializableqobject.h"
#include "../server/ServerCommunication/messageroutingtypes.h"
#include "../server/UserManagement/user.h"

class Message : public SerializableQObject
{
   Q_OBJECT
   Q_PROPERTY(quint16 destType READ getDestType WRITE setDestType)
   Q_PROPERTY(quint16 actionType READ getActionType WRITE setActionType)

protected:
    /* Constructor
     * in: Destination subsystem
     * in: Verb of the message
     * in: User associated with the message
     *      Can be null for messages that are to be sent to the
     *      client processes.
     *      Treated as a shared pointer.
     * Side Effects: None
     */
    explicit Message(DEST_TYPE, ACTION_TYPE, User*);

public:
    quint16 getDestType()   const { return (quint16)destType;   }
    quint16 getActionType() const { return (quint16)actionType; }

    void setDestType(quint16 dt)   { destType = static_cast<DEST_TYPE>(dt); }
    void setActionType(quint16 at) { actionType = static_cast<ACTION_TYPE>(at); }

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
    DEST_TYPE destType;
    ACTION_TYPE actionType;
    User* user;
};

#endif // MESSAGE_H
