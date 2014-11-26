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
* - Responsbile for passing around Message objects to the other client-side subsystems.
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
public:
    explicit Message(SerializableQObject *parent = 0);
    explicit Message(DEST_TYPE, ACTION_TYPE, QVector<SerializableQObject *>);

    quint16 getDestType()   const { return (quint16)destType;   }
    quint16 getActionType() const { return (quint16)actionType; }

    void setDestType(quint16 dt)   { destType = static_cast<DEST_TYPE>(dt); }
    void setActionType(quint16 at) { actionType = static_cast<ACTION_TYPE>(at); }

    QVector<SerializableQObject*> getData() const { return data; }
    virtual void insertToDataStream(QDataStream& ds) const;
    virtual void extractFromDataStream(QDataStream& ds);
private:
    DEST_TYPE destType;
    ACTION_TYPE actionType;
    QVector<SerializableQObject*> data;
};

#endif // MESSAGE_H
