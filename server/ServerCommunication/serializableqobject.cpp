#include "serializableqobject.h"

SerializableQObject::SerializableQObject(QObject *parent) :
    QObject(parent)
{
}

void SerializableQObject::insertToDataStream(QDataStream &ds, SerializableType type) const
{
}

void SerializableQObject::extractFromDataStream(QDataStream &ds)
{
}

QDataStream& operator<<(QDataStream& ds, const SerializableQObject& obj)
{
obj.insertToDataStream(ds);
return ds;
}

QDataStream& operator>>(QDataStream& ds, SerializableQObject** obj) // deprecated: throw( UserException )
{

}
