#ifndef SERIALIZABLEQOBJECT_H
#define SERIALIZABLEQOBJECT_H

/*
* serializableqobject.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* SerializableQObject class:
* - Base class for objects which can be polymorphically
*     serialized and deserialized.
*
* Traceability: CT-001
*
* Acknowledgements: None
*/

#include <QObject>
#include <QDataStream>
#include <QMetaProperty>
#include <QVariant>
#include "serializabletypes.h"

class SerializableQObject : public QObject
{
Q_OBJECT

protected:
    virtual void insertToDataStream(QDataStream& ds, SerializableType type) const;

public:
    virtual ~SerializableQObject(void);

    /* Member Function: insertToDataStream
     *   Serialization function, which must be overridden to
     *     insert the appropriate type constant
     *     into the data stream before the object's contents
     * inout: Data output stream
     * Side Effects: None
     * Return Value: None
     */
    virtual void insertToDataStream(QDataStream& ds) const = 0;

    /* Member Function: extractFromDataStream
     *   Deserialization function, which must be overridden by
     *     objects that need to deserialize more than
     *     just their properties.
     * inout: Data output stream
     * Side Effects: None
     * Return Value: None
     */
    virtual void extractFromDataStream(QDataStream& ds);
};

#endif // SERIALIZABLEQOBJECT_H
