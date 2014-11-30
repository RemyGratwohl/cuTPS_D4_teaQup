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
#include <QVector>
#include <QDataStream>
#include "../server/ServerCommunication/serializableqobject.h"
#include "../server/ServerCommunication/messageroutingtypes.h"


class Message : public SerializableQObject
{
   Q_OBJECT
   Q_PROPERTY(quint16 destType READ getDestType WRITE setDestType)
   Q_PROPERTY(quint16 actionType READ getActionType WRITE setActionType)

protected:
    /* Constructor
     * in: Destination subsystem
     * in: Verb of the message
     * Side Effects: None
     */
    explicit Message(DEST_TYPE, ACTION_TYPE);

public:
    quint16 getDestType()   const { return (quint16)destType;   }
    quint16 getActionType() const { return (quint16)actionType; }

    void setDestType(quint16 dt)   { destType = static_cast<DEST_TYPE>(dt); }
    void setActionType(quint16 at) { actionType = static_cast<ACTION_TYPE>(at); }

private:
    DEST_TYPE destType;
    ACTION_TYPE actionType;
};

#endif // MESSAGE_H
